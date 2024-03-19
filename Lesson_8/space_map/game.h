#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QFile>
#include <QDebug>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class Game;
}
QT_END_NAMESPACE

struct Player {
    int posx;
    int posy;
};

class Game : public QMainWindow
{
    Q_OBJECT

public:
    Game(QWidget *parent = nullptr);
    ~Game();

public slots:
    void renderMap();

private slots:
    void processPlayerMove(int x, int y);

protected:
    virtual void keyPressEvent(QKeyEvent *key);

private:
    Ui::Game *ui;
    QGraphicsScene *m_scene;

    QVector<QVector<char>> m_mapData;

    int m_HSize;
    int m_WSize;

    const int m_PixelSize = 40;

    Player m_player;

    bool loadMap();
    bool loadPlayerPos();
    bool checkPlayerCanMove(int x, int y);

    QPixmap getImage(char element);
};
#endif // GAME_H
