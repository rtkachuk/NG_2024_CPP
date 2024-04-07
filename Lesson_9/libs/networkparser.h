#ifndef NETWORKPARSER_H
#define NETWORKPARSER_H

#include <QObject>

#include <QJsonDocument>
#include <QJsonObject>

class NetworkParser
{
public:
    enum Action {
        noaction,
        move,
        pick,
        put,
        map,
        assignId,
        pos
    };

    enum Direction {
        nodirection,
        up,
        down,
        left,
        right
    };

    struct Request {
        QByteArray uuid;
        Action action;
        Direction direction;
        QString additionalInfo;
    };
    static Request parseRequest(QByteArray data);

    static Action parseAction(QString data);
    static Direction parseDirection(QString data);

    static QString actionToString(Action data);
    static QString directionToString(Direction data);
};

#endif // NETWORKPARSER_H
