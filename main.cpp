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
     InitWindow iw;
     iw.show();
     currentExitCode = a.exec();
    } while( currentExitCode == Game::EXIT_CODE_REBOOT );

    // main

    return currentExitCode;
}
