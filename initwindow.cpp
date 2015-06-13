#include "initwindow.h"
#include "ui_initwindow.h"

#include <QApplication>

InitWindow::InitWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InitWindow)
{
    ui->setupUi(this);
 /*   ui->buttonWidget->setStyleSheet(QStringLiteral("border-image: url(./slike/2/init.jpg);"));
    ui->pushButtonCreate->setStyleSheet(QStringLiteral("border-image: url();"));
    ui->pushButtonLoad->setStyleSheet(QStringLiteral("border-image: url(pom.jpg);"));
    ui->pushButtonExit->setStyleSheet(QStringLiteral("border-image: url();"));
*/
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
     game = new Game(); // sGame = new ServerGame();
     game->show();
     this->hide();
}

void InitWindow::on_pushButtonLoad_clicked()
{
    QString ipAddress = ui->inputIp->text();
    int port = ui->inputPort->text().toInt();

    // osnovna provera - ne vrsi posao kad dodje do conn errora
    if( ipAddress == "" || port == 0 )
        return;

    // ovcde treba neka provera, ako ne se javi conn error da ne otvara ovo
    // nego da ostane u initwindow za ponovni pokusaj
    cGame = new ClientGame(this, ipAddress, port);
    cGame->show();
    this->hide();
}
