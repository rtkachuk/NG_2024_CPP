#ifndef NETWORKER_H
#define NETWORKER_H

#include <QObject>
#include <QTcpSocket>

#include "../libs/networkparser.h"

class Networker : public QObject
{
    Q_OBJECT
public:
    explicit Networker(QObject *parent = nullptr);
    void connectToHost(QString ip, int port);
    QVector<QVector<char>> *getMap() { return &m_map; }
    void send(NetworkParser::Request request);

private slots:
    void connectedToHost();
    void readyRead();
    void processRawRequest(QByteArray rawRequest);

private:
    QTcpSocket *m_socket;
    QVector<QVector<char>> m_map;

    void saveMap(QString rawMap);

signals:
    void connected();
    void mapAvailable();
    void idAvailable(QString id);
    void movePlayer(QString playerInfo); // id,x,y
};

#endif // NETWORKER_H
