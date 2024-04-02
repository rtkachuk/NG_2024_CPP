#include "player.h"

Player::Player(QObject *parent, QString id)
    : QObject{parent}
{
    m_id = id;
}
