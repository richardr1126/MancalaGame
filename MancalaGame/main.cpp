#include "gamewindow.h"

#include <QApplication>
#include <QTime>

int main(int argc, char *argv[])
{
    srand(static_cast<unsigned>(QTime::currentTime().msec()));
    QApplication a(argc, argv);
    GameWindow w;
    w.show();
    return a.exec();
}
