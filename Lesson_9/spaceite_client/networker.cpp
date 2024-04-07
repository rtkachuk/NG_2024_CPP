#include "networker.h"

Networker::Networker(QObject *parent)
    : QObject{parent}
{
    m_socket = new QTcpSocket();

    connect (m_socket, &QTcpSocket::connected, this, &Networker::connectedToHost);
    connect (m_socket, &QTcpSocket::readyRead, this, &Networker::readyRead);
}

void Networker::connectToHost(QString ip, int port)
{
    m_socket->connectToHost(QHostAddress(ip), port);
}

void Networker::send(NetworkParser::Request request)
{
    QJsonObject json {
        {"action", NetworkParser::actionToString(request.action)},
        {"direction", NetworkParser::directionToString(request.direction)},
        {"addition", request.additionalInfo}
    };
    QJsonDocument jDoc { json };
    m_socket->write(jDoc.toJson());
    m_socket->flush();
}


void Networker::connectedToHost()
{
    emit connected();
}

void Networker::readyRead()
{
    QByteArray data = m_socket->readAll();

    qDebug() << data;
    qDebug() << "==================";
    while (data.indexOf("}\n{") != -1) {
        QByteArray package = data.sliced(0, data.indexOf("}\n{") + 1);
        qDebug() << package;
        qDebug() << "==================";
        data = data.remove(0, data.indexOf("}\n{") + QByteArray("}\n").size());
        processRawRequest(package);
    }
    processRawRequest(data);

    // How we can parse multiple json's at once?
    //
}

void Networker::processRawRequest(QByteArray rawRequest)
{
    NetworkParser::Request request = NetworkParser::parseRequest(rawRequest);

    qDebug() << request.action;
    switch (request.action) {
    case NetworkParser::map: saveMap(request.additionalInfo); break;
    case NetworkParser::pos: emit movePlayer(request.additionalInfo); break;
    case NetworkParser::assignId: emit idAvailable(request.additionalInfo); break;
    default: qDebug() << "TODO";
    }
}

void Networker::saveMap(QString rawMap)
{
    QStringList rawMapRows = rawMap.split(",");
    for (QString row : rawMapRows) {
        QVector<char> vectorRow;
        for (QChar item : row) {
            vectorRow.push_back(item.toLatin1());
        }
        m_map.push_back(vectorRow);
    }
    emit mapAvailable();
}
