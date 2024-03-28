#ifndef MAPWORKER_H
#define MAPWORKER_H

#include <QObject>
#include <QFile>

#include "logger.h"

class MapWorker : public QObject
{
    Q_OBJECT
public:
    explicit MapWorker(QObject *parent = nullptr);
    QVector<QVector<char>> getMap() { return m_mapData; }
    QString getMapString();

signals:
    void mapLoadingError();

private:
    bool loadMap();

    QVector<QVector<char>> m_mapData;
    Logger *m_logger;
};

#endif // MAPWORKER_H
