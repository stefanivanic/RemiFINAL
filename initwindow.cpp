#include "initwindow.h"
#include "ui_initwindow.h"

#include <QApplication>

InitWindow::InitWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InitWindow)
{
    ui->setupUi(this);
    ui->pushButtonLoad->setStyleSheet(QStringLiteral("border-image: url(./slike/Teme/2_load.jpg);"));
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

    QString ipAddress = ui->inputIp->text();
   /* int port = ui->inputPort->text().toInt();

    // osnovna provera - ne vrsi posao kad dodje do conn errora
    if( ipAddress == "" || port == 0 )
        return;

    cGame = new ClientGame(this, ipAddress, port);

    if( Client::CONN_ERROR == 1 ) {
        delete cGame;   return;
    }

    cGame->show();
    this->hide();*/
}
