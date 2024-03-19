#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui {
class Game;
}
QT_END_NAMESPACE

class Game : public QMainWindow
{
    Q_OBJECT

public:
    Game(QWidget *parent = nullptr);
    ~Game();

private slots:
    void createSquare();

private:
    Ui::Game *ui;
    QGraphicsScene *m_scene;
};
#endif // GAME_H
