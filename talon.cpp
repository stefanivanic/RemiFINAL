#include "talon.h"
#include "ui_talon.h"

Talon::Talon(QWidget *parent, int x, int y, int w, int h)
    : CardContainer(parent, x, y, w, h), ui(new Ui::Talon)
{
    ui->setupUi(this);
}

void Talon::printCards() {
    QString s;
    for(Card* c : cards)
        s.append(c->name()).append(" ");
    qDebug() << s;
}

//STEFANOV KOMENTAR
