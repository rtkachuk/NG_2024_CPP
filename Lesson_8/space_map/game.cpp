#include "game.h"
#include "ui_game.h"

Game::Game(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Game)
{
    ui->setupUi(this);
    m_scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(m_scene);

    loadMap();
    loadPlayerPos();
    renderMap();
}

Game::~Game()
{
    delete ui;
}

void Game::renderMap()
{
    int currentX = 0;
    int currentY = 0;
    m_scene->clear();
    for (QVector<char> row : m_mapData) {
        for (char item : row) {
            QGraphicsPixmapItem *tile = m_scene->addPixmap(getImage(item));
            tile->setPos(currentX * m_PixelSize, currentY * m_PixelSize);
            currentX++;
        }
        currentY++;
        currentX = 0;
    }

    QGraphicsPixmapItem *playerItem = m_scene->addPixmap(getImage('P'));
    playerItem->setPos(m_player.posx * m_PixelSize, m_player.posy * m_PixelSize);
    m_scene->update();
}

void Game::processPlayerMove(int x, int y)
{
    if (checkPlayerCanMove(x, y)) {
        m_player.posx = x;
        m_player.posy = y;
    }
}

void Game::keyPressEvent(QKeyEvent *key)
{
    switch (key->key()) {
    case Qt::Key_W: processPlayerMove(m_player.posx, m_player.posy-1); break;
    case Qt::Key_S: processPlayerMove(m_player.posx, m_player.posy+1); break;
    case Qt::Key_A: processPlayerMove(m_player.posx-1, m_player.posy); break;
    case Qt::Key_D: processPlayerMove(m_player.posx+1, m_player.posy); break;
    }
    renderMap();
}

bool Game::loadMap()
{
    QFile mapFile(":/Resources/misc/map.txt");
    if (mapFile.open(QIODevice::ReadOnly)) {
        QList<QByteArray> rows = mapFile.readAll().split('\n');
        for (QByteArray row : rows) {
            QVector<char> rowElements;
            if (row.size() * m_PixelSize > m_WSize)
                m_WSize = row.size() * m_PixelSize;
            for (char item : row) {
                rowElements.push_back(item);
            }
            m_mapData.push_back(rowElements);
        }

        m_HSize = m_mapData.size() * m_PixelSize;
        mapFile.close();
        return true;
    }
    qDebug() << mapFile.errorString();
    return false;
}

bool Game::loadPlayerPos()
{
    QFile file(":/Resources/misc/playerPos.txt");
    if (file.open(QIODevice::ReadOnly)) {
        QList<QByteArray> position = file.readAll().split('\n');
        m_player.posx = position[0].toInt();
        m_player.posy = position[1].toInt();
        qDebug() << "Player init position: " << m_player.posx << ":::" << m_player.posy;
        return true;
    }
    qDebug() << file.errorString();
    return false;
}

bool Game::checkPlayerCanMove(int x, int y)
{
    return m_mapData[y][x] == '.';
}

QPixmap Game::getImage(char element)
{
    QString elementName;
    switch (element) {
    case '.': elementName = "space/floor.png"; break;
    case '#': elementName = "space/wall.png"; break;
    case '*': elementName = "space/frog40.png"; break;
    case 'P': elementName = "player/player.png"; break;
    }
    return QPixmap(":/Resources/images/" + elementName);
}
