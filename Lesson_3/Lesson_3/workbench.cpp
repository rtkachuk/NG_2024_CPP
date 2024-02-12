#include "workbench.h"
#include "ui_workbench.h"

Workbench::Workbench(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Workbench)
{
    ui->setupUi(this);

    ui->pushButton->setStyleSheet("background-color: yellow");

    connect (ui->pushButton, &QPushButton::clicked, this, &Workbench::updateText);
    connect (ui->progressBarChanger, &QSlider::valueChanged, ui->progressBar, &QProgressBar::setValue);
}

Workbench::~Workbench()
{
    delete ui;
}

void Workbench::updateText()
{
    ui->label->setText("Привет :3");
}
