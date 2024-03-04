#ifndef ROFLCHAT_H
#define ROFLCHAT_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <QKeyEvent>
#include <QScrollBar>

#include <QJsonObject>
#include <QJsonDocument>

QT_BEGIN_NAMESPACE
namespace Ui {
class RoflChat;
}
QT_END_NAMESPACE

class RoflChat : public QMainWindow
{
    Q_OBJECT

public:
    RoflChat(QWidget *parent = nullptr);
    ~RoflChat();

protected:
    virtual void keyPressEvent(QKeyEvent *key);

private slots:
    void onConnect();
    void onDisconnect();
    void connectClicked();
    void onReceive();
    void onSend();

private:
    Ui::RoflChat *ui;
    QTcpSocket *m_socket;

    enum Screen {
        Login,
        Chat
    };

    QByteArray generateJson(QString type, QString value);
};
#endif // ROFLCHAT_H
