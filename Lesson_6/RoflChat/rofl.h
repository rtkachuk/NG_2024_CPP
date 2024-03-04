#ifndef ROFL_H
#define ROFL_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

#include <QJsonDocument>
#include <QJsonObject>

class Rofl : public QObject
{
    Q_OBJECT
public:
    explicit Rofl(QObject *parent = nullptr);
    ~Rofl();

private slots:
    void onClientConnected();
    void onClientSend();
    void sendToAll(QByteArray message);
    void onClientDisconnect();

public slots:
    void start(int port);

private:
    QTcpServer *m_server;
    QMap<QTcpSocket *, QByteArray> m_clients;

    struct clientCmd {
        QString type;
        QString value;
    };

    clientCmd parseJson(QByteArray data);
};

#endif // ROFL_H
