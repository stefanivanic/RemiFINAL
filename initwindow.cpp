#include "initwindow.h"
#include "ui_initwindow.h"

#include <QApplication>

InitWindow::InitWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InitWindow)
{
    ui->setupUi(this);
    this->setStyleSheet(QStringLiteral("border-image: url(./slike/2/init.jpg);"));
    ui->pushButtonCreate->setStyleSheet(QStringLiteral("border-image: url();font-size: 14pt;"));
    ui->pushButtonLoad->setStyleSheet(QStringLiteral("border-image: url();font-size: 14pt;"));
    ui->pushButtonExit->setStyleSheet(QStringLiteral("border-image: url();font-size: 14pt;"));
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

}
