#include "game.h"
#include "ui_game.h"

Game::Game(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Game)
{
    ui->setupUi(this);
    m_scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(m_scene);

    connect (ui->b_createSquare, &QPushButton::clicked, this, &Game::createSquare);
}

Game::~Game()
{
    delete ui;
}

void Game::createSquare()
{
    m_scene->addRect(ui->posx->value(), ui->posy->value(), ui->size->value(), ui->size->value());
    m_scene->update();
}
