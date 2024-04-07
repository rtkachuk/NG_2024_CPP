#include "servak.h"

Servak::Servak(QObject *parent)
    : QObject{parent}
{
    m_logger = new Logger(this, "CORE", true);

    m_mapworker = new MapWorker(this);
    m_networker = new NetWorker(this);

    m_networker->start(8080);

    connect (m_networker, &NetWorker::newPlayerArrived, this, &Servak::newClientArrived);
    connect (m_networker, &NetWorker::playerDisconnected, this, &Servak::onPlayerDisconnect);
    connect (m_networker, &NetWorker::playerCommand, this, &Servak::onPlayerCommand);
}

void Servak::newClientArrived(QByteArray id)
{
    manageNewPlayer(id);

}

void Servak::onPlayerCommand(NetworkParser::Request req)
{
    switch (req.action) {
    case NetworkParser::move: processPlayerMove(req.uuid, req.direction); break;
    default: m_logger->log("INVALID COMMAND GOT");
    }
}

void Servak::processPlayerMove(QByteArray id, NetworkParser::Direction direction)
{
    Player *player = m_players[id];
    Position pos = player->getPosition();

    switch(direction) {
    case NetworkParser::up: pos.y--; break;
    case NetworkParser::down: pos.y++; break;
    case NetworkParser::left: pos.x--; break;
    case NetworkParser::right: pos.x++; break;
    }
    if (m_mapworker->isPositionSteppable(pos)) {
        QString additionalInfo =QString("%1,%2,%3").arg(id)
                                     .arg(pos.x)
                                     .arg(pos.y);
        NetworkParser::Request request = prepareRequest(id, NetworkParser::pos, NetworkParser::nodirection, additionalInfo);
        player->setPosition(pos);
        m_networker->sendToAll(request);
    } else {
        m_logger->log(QString("Player moved wrongly %1: %2,%3").arg(id).arg(pos.x).arg(pos.y));
    }
}

NetworkParser::Request Servak::prepareRequest(QByteArray uuid, NetworkParser::Action action, NetworkParser::Direction direction, QString additionalInfo)
{
    NetworkParser::Request request;
    request.uuid = uuid;
    request.action = action;
    request.direction = direction;
    request.additionalInfo = additionalInfo;

    return request;
}

void Servak::onPlayerDisconnect(QByteArray id)
{
    delete m_players[id];
    m_players.remove(id);
}

void Servak::manageNewPlayer(QByteArray id)
{
    m_networker->sendToPlayer(id, prepareRequest("",
                                                 NetworkParser::map,
                                                 NetworkParser::nodirection,
                                                 m_mapworker->getMapString()));

    m_networker->sendToPlayer(id, prepareRequest("",
                                                 NetworkParser::assignId,
                                                 NetworkParser::nodirection,
                                                 QString::fromLocal8Bit(id)));

    m_networker->sendToAll(prepareRequest("",
                                          NetworkParser::pos,
                                          NetworkParser::nodirection,
                                          id + "," + m_mapworker->getBasicPlayerPositionString()));

    Player *player = new Player(this, QString::fromLocal8Bit(id));
    player->setPosition(m_mapworker->getBasicPlayerPosition());
    m_players[id] = player;

    for (Player *bufferPlayer : m_players) {
        m_networker->sendToPlayer(id, prepareRequest("",
                                                     NetworkParser::pos,
                                                     NetworkParser::nodirection,
                                                     bufferPlayer->getId().toLocal8Bit() + "," + bufferPlayer->getPositionByteArray()));
    }
    //m_players.append(new Player(this, QString::fromLocal8Bit(id)));
}
