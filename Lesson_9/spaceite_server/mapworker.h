#ifndef MAPWORKER_H
#define MAPWORKER_H

#include <QObject>
#include <QFile>

#include "logger.h"
#include "../libs/Position.h"

class MapWorker : public QObject
{
    Q_OBJECT
public:
    explicit MapWorker(QObject *parent = nullptr);
    QVector<QVector<char>> getMap() { return m_mapData; }
    QString getMapString();
    QString getBasicPlayerPositionString() { return m_defaultPlayerPostion;};
    Position getBasicPlayerPosition();
    bool isPositionSteppable(Position pos);


signals:
    void mapLoadingError();

private:
    bool loadMap();
    bool loadDefaultPlayerPosition();

    QVector<QVector<char>> m_mapData;
    QString m_defaultPlayerPostion;
    Logger *m_logger;
};

#endif // MAPWORKER_H
