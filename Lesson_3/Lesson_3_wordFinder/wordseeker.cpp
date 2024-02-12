#include "wordseeker.h"
#include "ui_wordseeker.h"

WordSeeker::WordSeeker(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WordSeeker)
{
    ui->setupUi(this);
    connect (ui->e_pattern, &QLineEdit::textChanged, this, &WordSeeker::counter);
    connect (ui->t_text, &QTextEdit::textChanged, this, &WordSeeker::counter);
}

WordSeeker::~WordSeeker()
{
    delete ui;
}

void WordSeeker::counter()
{
    QString text = ui->t_text->toPlainText();
    QString pattern = ui->e_pattern->text();

    if (text.isEmpty() || pattern.isEmpty()) return;

    int lastIndex = 0;
    int counter = 0;
    do {
        lastIndex = text.indexOf(pattern, lastIndex);
        if (lastIndex != -1) {
            counter++;
            lastIndex++;
        }
    } while (lastIndex != -1);
    ui->l_result->setText(QString("Результат: %1").arg(QString::number(counter)));
}
