#include "gamewindow.h"

#include <QTime>
#include <QApplication>

int main(int argc, char *argv[]) {
    srand(static_cast<unsigned>(QTime::currentTime().msec()));
    QApplication a(argc, argv);
    GameWindow w(nullptr);
    w.show();
    return a.exec();
}
