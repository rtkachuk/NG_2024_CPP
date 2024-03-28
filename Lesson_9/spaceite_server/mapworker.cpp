#include "mapworker.h"

MapWorker::MapWorker(QObject *parent)
    : QObject{parent}
{
    m_logger = new Logger(this, "MAP", true);

    if (loadMap() == false) {
        emit mapLoadingError();
    }
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
