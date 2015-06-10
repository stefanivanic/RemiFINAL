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
     ClientGame w;
>>>>>>> 688ce85cb87e641959b8f3293b78485d34d70e4a
     w.show();
     currentExitCode = a.exec();
    } while( currentExitCode == Game::EXIT_CODE_REBOOT );

    // main

    return currentExitCode;
}
