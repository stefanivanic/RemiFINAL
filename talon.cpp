#include "talon.h"
#include "ui_talon.h"

Talon::Talon(QWidget *parent, int x, int y, int w, int h)
    : CardContainer(parent, x, y, w, h), ui(new Ui::Talon)
{
    ui->setupUi(this);
    QPixmap pix(QDir::currentPath() + "/slike/2/talon.jpg");
    ui->label->setPixmap(pix);
}

void Talon::printCards() {
    QString s;
    for(Card* c : cards)
        s.append(c->name()).append(" ");
    qDebug() << s;
}

//STEFANOV KOMENTAR
