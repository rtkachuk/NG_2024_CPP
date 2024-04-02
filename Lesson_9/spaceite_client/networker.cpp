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


void Networker::connectedToHost()
{
    emit connected();
}

void Networker::readyRead()
{
    QByteArray data = m_socket->readAll();

    // How we can parse multiple json's at once?
    //

    processRawRequest(data);
}

void Networker::processRawRequest(QByteArray rawRequest)
{
    NetworkParser::Request request = NetworkParser::parseRequest(rawRequest);

    qDebug() << request.action;
    switch (request.action) {
    case NetworkParser::map: saveMap(request.additionalInfo); break;
    case NetworkParser::move: emit(request.additionalInfo); break;
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
