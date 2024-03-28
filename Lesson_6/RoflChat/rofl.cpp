#include "rofl.h"

Rofl::Rofl(QObject *parent)
    : QObject{parent}
{
    m_server = new QTcpServer(this);

    connect (m_server, &QTcpServer::newConnection, this, &Rofl::onClientConnected);
}

Rofl::~Rofl()
{
    if (m_server->isListening())
        m_server->close();

    delete m_server;
}

void Rofl::onClientConnected()
{
    QTcpSocket *client = m_server->nextPendingConnection();
    m_clients[client] = QByteArray("Anon");
    qDebug() << "Client connected!";

    connect (client, &QTcpSocket::readyRead, this, &Rofl::onClientSend);
    connect (client, &QTcpSocket::disconnected, this, &Rofl::onClientDisconnect);
}

void Rofl::onClientSend()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    QByteArray data = client->readAll();

    clientCmd action = parseJson(data);

    // { "type": "msg", "value": "Hello!" }
    // { "type": "nck", "value": "DonJuan" }
    //
    //

    if (action.type == "msg")
        sendToAll(m_clients[client] + ": " + action.value.toLocal8Bit());
    if (action.type == "nck")
        m_clients[client] = action.value.toLocal8Bit();
}

void Rofl::sendToAll(QByteArray message)
{
    for (QTcpSocket *client : m_clients.keys()) {
        client->write(message);
    }
}

void Rofl::onClientDisconnect()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    QByteArray login = m_clients[client];
    m_clients.remove(client);
    qDebug() << "Client disconnected!";

    sendToAll(QByteArray("<i>System: Client " + login + " has left us...</i>"));
}

void Rofl::start(int port)
{
    m_server->listen(QHostAddress::Any, port);
    if (m_server->isListening()) {
        qDebug() << "Server has been started at " << m_server->serverAddress().toString() << ":" << m_server->serverPort();
    }
}

Rofl::clientCmd Rofl::parseJson(QByteArray data)
{
    clientCmd action;
    QJsonObject json = QJsonDocument::fromJson(data).object();
    action.value = json.value("value").toString();
    action.type = json.value("type").toString();
    return action;
}
