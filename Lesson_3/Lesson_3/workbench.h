#ifndef WORKBENCH_H
#define WORKBENCH_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Workbench;
}
QT_END_NAMESPACE

class Workbench : public QMainWindow
{
    Q_OBJECT

public:
    Workbench(QWidget *parent = nullptr);
    ~Workbench();

private slots:
    void updateText();

private:
    Ui::Workbench *ui;
};
#endif // WORKBENCH_H
