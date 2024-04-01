#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);

    m_scene = new QGraphicsScene(this);
    ui->view->setScene(m_scene);

    m_socket = new QTcpSocket();

    ui->sb_port->setMaximum(16000);
    ui->e_ip->setText("127.0.0.1");
    ui->sb_port->setValue(8080);

    connect (ui->b_connect, &QPushButton::clicked, this, &Client::onConnectClicked);
    connect (m_socket, &QTcpSocket::connected, this, &Client::connectedToHost);
    connect (m_socket, &QTcpSocket::readyRead, this, &Client::readyRead);
}

Client::~Client()
{
    delete ui;
}

void Client::onConnectClicked()
{
    m_socket->connectToHost(QHostAddress(ui->e_ip->text()), ui->sb_port->value());
}

void Client::connectedToHost()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Client::readyRead()
{
    Map map;

    map.downloadedMap = downloadMap();
    map.rawMap = map.downloadedMap.split(",");
    m_map.clear();

    saveMap(map.rawMap);
    renderMap();
}

QString Client::downloadMap()
{
    QJsonObject json = QJsonDocument::fromJson(m_socket->readAll()).object();

    qDebug()<<json;
    return json.value("addition").toString();
}

void Client::saveMap(QStringList rawMap)
{
    for (QString row : rawMap) {
        QVector<char> vectorRow;
        for (QChar item : row) {
            vectorRow.push_back(item.toLatin1());
        }
        m_map.push_back(vectorRow);
    }
}


void Client::renderMap()
{
    int currentX = 0;
    int currentY = 0;
    m_scene->clear();
    for (QVector<char> row : m_map) {
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
