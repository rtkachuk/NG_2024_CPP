#include "networkparser.h"

NetworkParser::Request NetworkParser::parseRequest(QByteArray data)
{
    NetworkParser::Request request;

    QJsonObject json = QJsonDocument::fromJson(data).object();
    request.action = parseAction(json.value("action").toString());
    request.direction = parseDirection(json.value("direction").toString());
    request.additionalInfo = json.value("addition").toString();
    return request;
}

NetworkParser::Action NetworkParser::parseAction(QString data)
{
    if (data == "move") return Action::move;
    if (data == "pick") return Action::pick;
    if (data == "put") return Action::put;
    if (data == "map") return Action::map;
    if (data == "assignid") return Action::assignId;
    if (data == "pos") return Action::pos;
    return Action::noaction;
}

NetworkParser::Direction NetworkParser::parseDirection(QString data)
{
    if (data == "up") return Direction::up;
    if (data == "down") return Direction::down;
    if (data == "left") return Direction::left;
    if (data == "right") return Direction::right;
    return Direction::nodirection;
}

QString NetworkParser::actionToString(Action data)
{
    switch (data) {
    case Action::assignId: return "assignid"; break;
    case Action::pos: return "pos"; break;
    case Action::move: return "move"; break;
    case Action::map: return "map"; break;
    case Action::pick: return "pick"; break;
    case Action::put: return "put"; break;
    default: return "";
    }
}

QString NetworkParser::directionToString(Direction data)
{
    switch (data) {
    case Direction::up: return "up"; break;
    case Direction::down: return "down"; break;
    case Direction::left: return "left"; break;
    case Direction::right: return "right"; break;
    default: return "";
    }
}
