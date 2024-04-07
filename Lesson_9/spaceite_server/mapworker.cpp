#include "mapworker.h"

MapWorker::MapWorker(QObject *parent)
    : QObject{parent}
{
    m_logger = new Logger(this, "MAP", true);
    m_defaultPlayerPostion = "0,0";

    if (loadMap() == false) {
        emit mapLoadingError();
    }

    loadDefaultPlayerPosition();
}

QString MapWorker::getMapString()
{
    QString responce;
    for (QVector<char> row : m_mapData) {
        for (char item : row) {
            responce += item;
        }
        responce += ",";
    }
    return responce;
}

Position MapWorker::getBasicPlayerPosition()
{
    QStringList positionxy = m_defaultPlayerPostion.split(',');
    Position pos;
    pos.x = positionxy[0].toInt();
    pos.y = positionxy[1].toInt();
    return pos;
}

bool MapWorker::isPositionSteppable(Position pos)
{
    return m_mapData[pos.y][pos.x] == '.';
}

bool MapWorker::loadMap()
{
    m_mapData.clear();
    QFile mapFile(":/Resources/misc/map.txt");
    if (mapFile.open(QIODevice::ReadOnly)) {
        QList<QByteArray> rows = mapFile.readAll().split('\n');
        for (QByteArray row : rows) {
            QVector<char> rowElements;
            for (char item : row) {
                rowElements.push_back(item);
            }
            m_mapData.push_back(rowElements);
        }

        mapFile.close();
        m_logger->log("Map loaded successfully!");
        return true;
    }
    m_logger->log(mapFile.errorString());
    return false;
}

bool MapWorker::loadDefaultPlayerPosition()
{
    QFile posFile(":/Resources/misc/playerPos.txt");
    if (posFile.open(QIODevice::ReadOnly)) {
        QList<QByteArray> rows = posFile.readAll().split('\n');
        m_defaultPlayerPostion = rows[0] + "," + rows[1];
        m_logger->log("Loaded default player position: " + m_defaultPlayerPostion);
        return true;
    }
    m_logger->log(posFile.errorString());
    return false;
}
