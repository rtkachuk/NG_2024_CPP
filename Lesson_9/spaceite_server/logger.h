#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QDebug>

class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger(QObject *parent, QString type, bool debugMode);
    void log(QString message);
    void debug(QString message);

private:

    QString m_type;
    bool m_debug;
};

#endif // LOGGER_H
