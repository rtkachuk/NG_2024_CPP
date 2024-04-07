#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "../libs/Position.h"

class Player : public QObject
{
    Q_OBJECT
public:

    explicit Player(QObject *parent = nullptr);
    explicit Player(QObject *parent = nullptr, QString id = "");

    Position getPosition() { return m_position; }
    void setPosition(Position pos) { m_position = pos; }
    QString getId() { return m_id; }
    void setId(QString id) { m_id = id; }

    QByteArray getPositionByteArray() { return QString("%1,%2").arg(m_position.x).arg(m_position.y).toLocal8Bit(); }
private:
    Position m_position;
    QString m_id;

signals:
};

#endif // PLAYER_H
