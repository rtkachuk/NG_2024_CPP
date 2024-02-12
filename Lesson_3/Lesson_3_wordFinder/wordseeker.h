#ifndef WORDSEEKER_H
#define WORDSEEKER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class WordSeeker;
}
QT_END_NAMESPACE

class WordSeeker : public QMainWindow
{
    Q_OBJECT

public:
    WordSeeker(QWidget *parent = nullptr);
    ~WordSeeker();

private slots:
    void counter();

private:
    Ui::WordSeeker *ui;
};
#endif // WORDSEEKER_H
