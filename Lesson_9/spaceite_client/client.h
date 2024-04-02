#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QJsonDocument>
#include <QJsonObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QDebug>

#include "networker.h"

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

    struct Map {
        QString downloadedMap;
        QStringList rawMap;
    };

private slots:
    void connectedToHost();
    void onConnectClicked();
    void renderMap();
    void assignId(QString id) { m_id = id; };
    void movePlayer(QString playerInfo);

private:
    QJsonObject jsonDownloaded;
    QPixmap getImage(char element);

    QGraphicsScene *m_scene;
    Ui::Client *ui;

    Networker *m_networker;
    QString m_id;

    QMap<QString, QGraphicsPixmapItem *> m_players;
};
#endif // CLIENT_H
