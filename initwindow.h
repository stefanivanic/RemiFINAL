#ifndef INITWINDOW_H
#define INITWINDOW_H

#include <QApplication>
#include <QDialog>
#include "servergame.h"
#include "clientgame.h"

namespace Ui {
class InitWindow;
}

class InitWindow : public QDialog
{
    Q_OBJECT

public:
    explicit InitWindow(QWidget *parent = 0);
    ~InitWindow();

private slots:
    void on_pushButtonExit_clicked();

    void on_pushButtonCreate_clicked();

    void on_pushButtonLoad_clicked();

private:
    Ui::InitWindow *ui;

    ServerGame* sGame;
    ClientGame* cGame;
    Game*       game; // samo za debug

};

#endif // INITWINDOW_H
