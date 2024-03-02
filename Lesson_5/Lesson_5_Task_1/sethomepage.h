#ifndef SETHOMEPAGE_H
#define SETHOMEPAGE_H

#include <QDialog>

namespace Ui {
class SetHomePage;
}

class SetHomePage : public QDialog
{
    Q_OBJECT

public:
    explicit SetHomePage(QWidget *parent = nullptr);
    explicit SetHomePage(QString homePage, QWidget *parent = nullptr);
    ~SetHomePage();
    void setHomepage(QString homepage) { m_homepage = homepage; }
    QString getHomepage() { return m_homepage; }

private slots:
    void okClicked();

private:
    Ui::SetHomePage *ui;
    QString m_homepage;
};

#endif // SETHOMEPAGE_H
