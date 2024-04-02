#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class Player : public QObject
{
    Q_OBJECT
public:
    struct Position {
        int x;
        int y;
    };

    explicit Player(QObject *parent = nullptr);
    explicit Player(QObject *parent = nullptr, QString id = "");

    Position getPosition() { return m_position; }
    void setPosition(Position pos) { m_position = pos; }
private:
    Position m_position;
    QString m_id;

signals:
};

#endif // PLAYER_H
