#include "initwindow.h"
#include "ui_initwindow.h"

#include <QApplication>

InitWindow::InitWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InitWindow)
{
    ui->setupUi(this);

    ui->buttonWidget->setStyleSheet(QStringLiteral("border-image: url(./slike/Teme/2_init.jpg);"));
    ui->pushButtonCreate->setStyleSheet(QStringLiteral("border-image: url(./slike/Teme/2_create.jpg);"));
    ui->pushButtonLoad->setStyleSheet(QStringLiteral("border-image: url(./slike/Teme/2_load.jpg);"));
    ui->pushButtonExit->setStyleSheet(QStringLiteral("border-image: url(./slike/Teme/2_exit.jpg);"));
    ui->labelIp->setStyleSheet(QStringLiteral("border-image: url(./slike/Teme/2_ipport.jpg);"));

    ui->inputIp->hide();
    ui->labelIp->hide();
}

InitWindow::~InitWindow()
{
    delete ui;
}

void InitWindow::on_pushButtonExit_clicked()
{
    this->close();
}

void InitWindow::on_pushButtonCreate_clicked()
{
      sGame = new ServerGame(); // sGame = new ServerGame();

      sGame->show();

  //  game = new Game();
  //  game->show();

     this->hide();
}

void InitWindow::on_pushButtonLoad_clicked()
{
    ui->pushButtonLoad->setStyleSheet(QStringLiteral("border-image: url(./slike/Teme/2_join.jpg);"));
    ui->inputIp->show();
    ui->labelIp->show();

    QStringList list = ui->inputIp->text().split(":");

    if(list.size()<2 || list.size()>2)
    {
        return;
    }
    QString ipAddress = list[0];
    int port = list[1].toInt();

    cGame = new ClientGame(this, ipAddress, port);

    if( Client::CONN_ERROR == 1 ) {
        delete cGame;   return;
    }

    cGame->show();
    this->hide();
}
