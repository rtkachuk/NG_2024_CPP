#include "networker.h"

NetWorker::NetWorker(QObject *parent)
    : QObject{parent}
{
    m_server = new QTcpServer(this);
    m_logger = new Logger(this, "NETWORKING", true);

    connect (m_server, &QTcpServer::newConnection, this, &NetWorker::onPlayerConnected);
}

bool NetWorker::start(int port)
{
    bool ok = m_server->listen(QHostAddress::Any, port);
    if (m_server->isListening()) {
        m_logger->log(QString("Server has been started at %1:%2")
                          .arg(m_server->serverAddress().toString())
                          .arg(m_server->serverPort()));
    }

    if (ok == false) {
        m_logger->log(m_server->errorString());
    }

    return ok;
}

void NetWorker::sendToPlayer(QByteArray id, Request request)
{
    QJsonObject json {
                     {"action", actionToString(request.action)},
        {"direction", directionToString(request.direction)},
        {"addition", request.additionalInfo}
    };
    QJsonDocument jDoc { json };
    m_clients[id]->write(jDoc.toJson());
}

void NetWorker::sendToAll(QByteArray data)
{
    for (QByteArray id : m_clients.keys()) {
        m_clients[id]->write(data);
    }
}

void NetWorker::onPlayerCommand()
{
    QTcpSocket *client = m_server->nextPendingConnection();
    Request request = parseRequest(client->readAll());
    emit playerCommand(request);
}

void NetWorker::onPlayerConnected()
{
    QTcpSocket *client = m_server->nextPendingConnection();
    QByteArray id = QUuid::createUuid().toByteArray();
    m_clients[id] = client;
    m_logger->log(QString("New client connected: %1")
                      .arg(id));

    connect (client, &QTcpSocket::readyRead, this, &NetWorker::onPlayerCommand);
    connect (client, &QTcpSocket::disconnected, this, &NetWorker::onPlayerDisconnected);
    emit newPlayerArrived(id);
}

void NetWorker::onPlayerDisconnected()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    for (QByteArray id : m_clients.keys()) {
        if (m_clients[id] == client) {
            m_logger->log(QString("Client disconnected: %s")
                              .arg(id));
            emit playerDisconnected(id);
            m_clients.remove(id);
        }
    }
}

NetWorker::Request NetWorker::parseRequest(QByteArray data)
{
    NetWorker::Request request;

    QJsonObject json = QJsonDocument::fromJson(data).object();
    request.action = parseAction(json.value("action").toString());
    request.direction = parseDirection(json.value("direction").toString());
    request.additionalInfo = json.value("addition").toString();
    return request;
}

NetWorker::Action NetWorker::parseAction(QString data)
{
    if (data == "move") return Action::move;
    if (data == "pick") return Action::pick;
    if (data == "put") return Action::put;
    return Action::noaction;
}

NetWorker::Direction NetWorker::parseDirection(QString data)
{
    if (data == "up") return Direction::up;
    if (data == "down") return Direction::down;
    if (data == "left") return Direction::left;
    if (data == "right") return Direction::right;
    return Direction::nodirection;
}

QString NetWorker::actionToString(Action data)
{
    switch (data) {
    case Action::move: return "move"; break;
    case Action::map: return "map"; break;
    case Action::pick: return "pick"; break;
    case Action::put: return "put"; break;
    default: return "";
    }
}

QString NetWorker::directionToString(Direction data)
{
    switch (data) {
    case Direction::up: return "up"; break;
    case Direction::down: return "down"; break;
    case Direction::left: return "left"; break;
    case Direction::right: return "right"; break;
    default: return "";
    }
}
