#include <QCoreApplication>
#include "rofl.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Rofl *servak = new Rofl();
    servak->start(8080);

    return a.exec();
}
