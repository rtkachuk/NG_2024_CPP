#include "logger.h"

Logger::Logger(QObject *parent, QString type, bool debugMode)
    : QObject{parent}
{
    m_type = type;
    m_debug = debugMode;

    log("Module " + type + " initialized!");
}

void Logger::log(QString message)
{
    qDebug() << "[" << m_type << "]: " << message;
}

void Logger::debug(QString message)
{
    if (m_debug) {
        log(message);
    }
}
