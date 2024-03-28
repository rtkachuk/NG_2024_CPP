#ifndef NETWORKER_H
#define NETWORKER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUuid>
#include <QJsonDocument>
#include <QJsonObject>

#include "logger.h"

class NetWorker : public QObject
{
    Q_OBJECT
public:

    enum Action {
        noaction,
        move,
        pick,
        put,
        map
    };

    enum Direction {
        nodirection,
        up,
        down,
        left,
        right
    };

    struct Request {
        QByteArray uuid;
        Action action;
        Direction direction;
        QString additionalInfo;
    };

    explicit NetWorker(QObject *parent = nullptr);
    bool start(int port);

public slots:
    void sendToPlayer(QByteArray id, Request request);
    void sendToAll(QByteArray data);

private slots:
    void onPlayerCommand();
    void onPlayerConnected();
    void onPlayerDisconnected();

signals:
    void newPlayerArrived(QByteArray id);
    void playerDisconnected(QByteArray id);
    void playerCommand(Request request);

private:

    Request parseRequest(QByteArray data);

    Action parseAction(QString data);
    Direction parseDirection(QString data);

    QString actionToString(Action data);
    QString directionToString(Direction data);

    QTcpServer *m_server;
    QMap<QByteArray, QTcpSocket *> m_clients;
    Logger *m_logger;
};

#endif // NETWORKER_H
