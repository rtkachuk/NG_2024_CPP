#ifndef SERVAK_H
#define SERVAK_H

#include <QObject>
#include "networker.h"
#include "mapworker.h"
#include "logger.h"

class Servak : public QObject
{
    Q_OBJECT
public:
    explicit Servak(QObject *parent = nullptr);

private slots:
    void newClientArrived(QByteArray id);

signals:

private:
    Logger *m_logger;

    NetWorker *m_networker;
    MapWorker *m_mapworker;
};

#endif // SERVAK_H
