#include "game.h"
#include "clientgame.h"
#include "servergame.h"
#include "initwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    int currentExitCode = 0;

    do {
     QApplication a(argc, argv);
<<<<<<< HEAD
     InitWindow w;
=======
     Game w;
>>>>>>> 9d7a288d95ad64a13bcfc58e4decc99dc403ec52
     w.show();
     currentExitCode = a.exec();
    } while( currentExitCode == Game::EXIT_CODE_REBOOT );

    // main

    return currentExitCode;
}
