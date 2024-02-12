#include "numbers.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Numbers w;
    w.show();
    return a.exec();
}
