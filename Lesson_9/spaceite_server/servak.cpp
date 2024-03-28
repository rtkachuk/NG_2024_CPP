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
    NetWorker::Request request;
    request.uuid = "";
    request.action = NetWorker::map;
    request.direction = NetWorker::nodirection;
    request.additionalInfo = m_mapworker->getMapString();

    m_networker->sendToPlayer(id, request);
}
