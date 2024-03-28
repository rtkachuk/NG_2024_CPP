#include "roflchat.h"
#include "ui_roflchat.h"

RoflChat::RoflChat(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RoflChat)
{
    ui->setupUi(this);

    m_socket = new QTcpSocket();

    ui->sb_port->setMaximum(16000);

    ui->e_chat->setReadOnly(true);
    ui->e_users->setReadOnly(true);

    connect (m_socket, &QTcpSocket::connected, this, &RoflChat::onConnect);
    connect (m_socket, &QTcpSocket::disconnected, this, &RoflChat::onDisconnect);
    connect (m_socket, &QTcpSocket::readyRead, this, &RoflChat::onReceive);

    connect (ui->b_connect, &QPushButton::clicked, this, &RoflChat::connectClicked);
}

RoflChat::~RoflChat()
{
    m_socket->disconnectFromHost();

    delete m_socket;
    delete ui;
}

void RoflChat::keyPressEvent(QKeyEvent *key)
{
    if (ui->stackedWidget->currentIndex() == Screen::Login) {
        return;
    }

    if (key->modifiers() == Qt::ControlModifier) {
        if (key->key() == Qt::Key_Return) {
            onSend();
        }
    }
}

void RoflChat::onConnect()
{
    ui->stackedWidget->setCurrentIndex(Screen::Chat);

    m_socket->write(generateJson("nck", ui->e_login->text()));

    // { "type": "nck", "value": "DonJuan" }
}

void RoflChat::onDisconnect()
{
    ui->stackedWidget->setCurrentIndex(Screen::Login);
}

void RoflChat::connectClicked()
{
    QHostAddress address = QHostAddress(ui->e_address->text());
    int port = ui->sb_port->value();

    m_socket->connectToHost(address, port);
}

void RoflChat::onReceive()
{
    QString message = m_socket->readAll();
    QString text = ui->e_chat->toHtml();
    ui->e_chat->setHtml(text + message);
    ui->e_chat->verticalScrollBar()->setValue(ui->e_chat->verticalScrollBar()->maximum());
}

void RoflChat::onSend()
{

    QString message = ui->e_input->toPlainText();
    m_socket->write(generateJson("msg", message));
}

//
// Just create function, that will make all json
// stuff for me

QByteArray RoflChat::generateJson(QString type, QString value)
{
    QJsonObject json {
        {"type", type},
        {"value", value}
    };
    QJsonDocument jDoc { json };
    return jDoc.toJson();
}
