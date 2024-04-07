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

void NetWorker::sendToPlayer(QByteArray id, NetworkParser::Request request)
{
    QJsonObject json {
                     {"action", NetworkParser::actionToString(request.action)},
        {"direction", NetworkParser::directionToString(request.direction)},
        {"addition", request.additionalInfo}
    };
    QJsonDocument jDoc { json };
    m_clients[id]->write(jDoc.toJson());
    m_clients[id]->flush();
}

void NetWorker::sendToAll(NetworkParser::Request request)
{
    QJsonObject json {
        {"action", NetworkParser::actionToString(request.action)},
        {"direction", NetworkParser::directionToString(request.direction)},
        {"addition", request.additionalInfo}
    };
    QJsonDocument jDoc { json };
    QByteArray data = jDoc.toJson();
    for (QByteArray id : m_clients.keys()) {
        m_clients[id]->write(data);
        m_clients[id]->flush();
    }
}

void NetWorker::onPlayerCommand()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    NetworkParser::Request request = NetworkParser::parseRequest(client->readAll());

    for (QByteArray key : m_clients.keys()) {
        if (m_clients[key] == client) {
            request.uuid = key;
            break;
        }
    }

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
            m_logger->log(QString("Client disconnected: %1")
                              .arg(id));
            emit playerDisconnected(id);
            m_clients.remove(id);
        }
    }
}
