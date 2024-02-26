#ifndef LUNA_H
#define LUNA_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QMenu>
#include <QAction>

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
    void tabChanged();
    void titleChanged(QString title);

private:
    Ui::Luna *ui;
    QMenu *m_fileMenu;
    QAction *m_quit;
    QAction *m_addWidget;
    QMap<int, QWebEngineView *> tabs;
};
#endif // LUNA_H
