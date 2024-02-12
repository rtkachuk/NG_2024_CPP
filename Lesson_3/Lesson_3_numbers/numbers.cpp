#include "numbers.h"
#include "ui_numbers.h"

Numbers::Numbers(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Numbers)
{
    ui->setupUi(this);
    m_summ = 0;

    ui->dial->setRange(0, 100);

    connect (ui->dial, &QDial::valueChanged, ui->s_number, &QSpinBox::setValue);
    connect (ui->b_add, &QPushButton::clicked, this, &Numbers::add);
}

Numbers::~Numbers()
{
    delete ui;
}

void Numbers::add()
{
    m_summ = m_summ + ui->dial->value();
    ui->statusbar->showMessage(QString::number(m_summ));
}
