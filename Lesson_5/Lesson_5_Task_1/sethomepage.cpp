#include "sethomepage.h"
#include "ui_sethomepage.h"

SetHomePage::SetHomePage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SetHomePage)
{
    ui->setupUi(this);
}

SetHomePage::SetHomePage(QString homePage, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SetHomePage)
{
    ui->setupUi(this);
    ui->e_homepage->setText(homePage);
    m_homepage = homePage;

    connect (ui->buttonBox, &QDialogButtonBox::accepted, this, &SetHomePage::okClicked);
}

SetHomePage::~SetHomePage()
{
    delete ui;
}

void SetHomePage::okClicked()
{
    m_homepage = ui->e_homepage->text();
    this->accept();
}
