#include <QCoreApplication>
#include "servak.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Servak *ser = new Servak();
    return a.exec();
}
