#include "luna.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setAttribute(Qt::AA_DontUseNativeMenuBar);
    Luna w;
    w.show();
    return a.exec();
}
