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
     game = new Game();
     game->show();
     this->hide();
}
