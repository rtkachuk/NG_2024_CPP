#ifndef NUMBERS_H
#define NUMBERS_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Numbers;
}
QT_END_NAMESPACE

class Numbers : public QMainWindow
{
    Q_OBJECT

public:
    Numbers(QWidget *parent = nullptr);
    ~Numbers();

private slots:
    void add();

private:
    Ui::Numbers *ui;
    int m_summ;
};
#endif // NUMBERS_H
