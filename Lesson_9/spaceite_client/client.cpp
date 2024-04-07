#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);

    m_scene = new QGraphicsScene(this);
    ui->view->setScene(m_scene);

    m_networker = new Networker(this);

    ui->sb_port->setMaximum(16000);
    ui->e_ip->setText("127.0.0.1");
    ui->sb_port->setValue(8080);

    connect(m_networker, &Networker::connected, this, &Client::connectedToHost);
    connect(m_networker, &Networker::mapAvailable, this, &Client::renderMap);
    connect(m_networker, &Networker::idAvailable, this, &Client::assignId);
    connect(m_networker, &Networker::movePlayer, this, &Client::updatePlayerPos);

    connect (ui->b_connect, &QPushButton::clicked, this, &Client::onConnectClicked);
}

Client::~Client()
{
    delete ui;
}

void Client::onConnectClicked()
{
    m_networker->connectToHost(ui->e_ip->text(), ui->sb_port->value());
}

void Client::connectedToHost()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Client::renderMap()
{
    int currentX = 0;
    int currentY = 0;
    m_scene->clear();
    qDebug() << m_networker->getMap()->size();
    for (QVector<char> row : *(m_networker->getMap())) {
        for (char item : row) {
            QGraphicsPixmapItem *tile = m_scene->addPixmap(getImage(item));
            tile->setPos(currentX * 40, currentY * 40);
            currentX++;
        }
        currentY++;
        currentX = 0;
    }
    m_scene->update();
}

void Client::assignId(QString id)
{
    qDebug() << "ID Assigned: " << id;
    m_id = id;
}

void Client::updatePlayerPos(QString playerInfo)
{
    QStringList playerData = playerInfo.split(",");

    qDebug() << "Moving player";
    QString id = playerData[0];
    int x = playerData[1].toInt();
    int y = playerData[2].toInt();
    QGraphicsPixmapItem *item = nullptr;

    if (m_players.contains(id)) {
        item = m_players[id];
    } else {
        item = m_scene->addPixmap(QPixmap(":/Resources/images/player/player.png"));
        m_players[id] = item;
    }

    qDebug() << QString("POS: %1,%2; SCENE: %3,%4").arg(x).arg(y).arg(40*x).arg(40*y);

    item->setPos(40 * x, 40 * y);
    m_scene->update();

}

void Client::processPlayerMove(NetworkParser::Direction direction)
{
    NetworkParser::Request request;

    qDebug() << "MOVE";
    request.uuid = m_id.toLocal8Bit();
    request.direction = direction;
    request.action = NetworkParser::move;
    request.additionalInfo = "";

    qDebug() << "UUID: " << request.uuid;

    m_networker->send(request);
}

void Client::keyPressEvent(QKeyEvent *key)
{
    switch (key->key()) {
    case Qt::Key_W: processPlayerMove(NetworkParser::up); break;
    case Qt::Key_S: processPlayerMove(NetworkParser::down); break;
    case Qt::Key_A: processPlayerMove(NetworkParser::left); break;
    case Qt::Key_D: processPlayerMove(NetworkParser::right); break;
    }
}

QPixmap Client::getImage(char element)
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
