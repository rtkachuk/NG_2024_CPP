#include "workbench.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Workbench w;
    w.show();
    return a.exec();
}
