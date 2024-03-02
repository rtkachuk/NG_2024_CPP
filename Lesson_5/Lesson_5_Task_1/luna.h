#ifndef LUNA_H
#define LUNA_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QMenu>
#include <QAction>
#include <QDebug>

#include "sethomepage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Luna;
}
QT_END_NAMESPACE

class Luna : public QMainWindow
{
    Q_OBJECT

public:
    Luna(QWidget *parent = nullptr);
    ~Luna();

private slots:
    void openLink();
    void updateURL(QUrl url);
    void addTab();
    void removeTab(int index);
    void tabChanged(int index);
    void titleChanged(QString title);

    void updateHomepage();

private:
    Ui::Luna *ui;
    QMenu *m_fileMenu;
    QMenu *m_settingsMenu;

    QAction *m_quit;
    QAction *m_addTab;
    QAction *m_reloadTab;

    QAction *m_updateHomepage;

    QMap<QWidget *, QWebEngineView *> m_tabs;
    QVector<QMetaObject::Connection> m_tabDynamicConnections;

    QString m_homepage;

    void debug(QString message);
};
#endif // LUNA_H
