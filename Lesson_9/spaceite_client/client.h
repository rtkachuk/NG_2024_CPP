#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui {
class Client;
}
QT_END_NAMESPACE

class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget *parent = nullptr);
    ~Client();

private slots:
    void onConnectClicked();
    void connectedToHost();
    void readyRead();
    void renderMap();
    void parseMap(QString);

private:
    QPixmap getImage(char element);
    QTcpSocket *m_socket;
    QVector<QVector<char>> m_map;
    QGraphicsScene *m_scene;
    Ui::Client *ui;
};
#endif // CLIENT_H
