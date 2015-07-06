#include <QApplication>

#include "ui/start_screen/startscreen.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartScreen *sc = new StartScreen();
    sc->show();

    return a.exec();
}
