#include <QtGui/QApplication>
#include "crftagrobot.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CRFTagRobot w;
    w.show();

    return a.exec();
}
