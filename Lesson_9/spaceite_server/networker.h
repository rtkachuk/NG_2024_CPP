#ifndef NETWORKER_H
#define NETWORKER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUuid>
#include <QJsonDocument>
#include <QJsonObject>
#include "../libs/networkparser.h"

#include "logger.h"

class NetWorker : public QObject
{
    Q_OBJECT
public:

    explicit NetWorker(QObject *parent = nullptr);
    bool start(int port);

public slots:
    void sendToPlayer(QByteArray id, NetworkParser::Request request);
    void sendToAll(NetworkParser::Request request);

private slots:
    void onPlayerCommand();
    void onPlayerConnected();
    void onPlayerDisconnected();

signals:
    void newPlayerArrived(QByteArray id);
    void playerDisconnected(QByteArray id);
    void playerCommand(NetworkParser::Request request);

private:

    QTcpServer *m_server;
    QMap<QByteArray, QTcpSocket *> m_clients;
    Logger *m_logger;
};

#endif // NETWORKER_H
