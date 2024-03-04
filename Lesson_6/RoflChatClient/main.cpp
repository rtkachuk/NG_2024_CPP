#include "roflchat.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RoflChat w;
    w.show();
    return a.exec();
}
