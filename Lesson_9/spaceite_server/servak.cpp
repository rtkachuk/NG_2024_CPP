#include "servak.h"

Servak::Servak(QObject *parent)
    : QObject{parent}
{
    m_logger = new Logger(this, "CORE", true);

    m_mapworker = new MapWorker(this);
    m_networker = new NetWorker(this);

    m_networker->start(8080);

    connect (m_networker, &NetWorker::newPlayerArrived, this, &Servak::newClientArrived);
}

void Servak::newClientArrived(QByteArray id)
{
    manageNewPlayer(id);

}

void Servak::manageNewPlayer(QByteArray id)
{
    NetworkParser::Request request;
    request.uuid = "";
    request.action = NetworkParser::map;
    request.direction = NetworkParser::nodirection;
    request.additionalInfo = m_mapworker->getMapString();

    m_networker->sendToPlayer(id, request);

    request.uuid = "";
    request.action = NetworkParser::assignId;
    request.direction = NetworkParser::nodirection;
    request.additionalInfo = QString::fromLocal8Bit(id);

    m_networker->sendToPlayer(id, request);

    request.uuid = "";
    request.action = NetworkParser::move;
    request.direction = NetworkParser::nodirection;
    request.additionalInfo = id + "," + m_mapworker->getBasicPlayerPosition();

    m_networker->sendToPlayer(id, request);

    m_players.append(new Player(this, QString::fromLocal8Bit(id)));
}
