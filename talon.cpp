#include "talon.h"
#include "ui_talon.h"

Talon::Talon(QWidget *parent, int x, int y, int w, int h)
    : CardContainer(parent, x, y, w, h)
{
        /* background color , bolje da se zameni sa setStyleSheet*/
        QPalette Pal(palette());
        Pal.setColor(QPalette::Background, Qt::lightGray);
        this->setAutoFillBackground(true);
        this->setPalette(Pal);
}

void Talon::printCards() {
    QString s;
    for(Card* c : cards)
        s.append(c->name()).append(" ");
    qDebug() << s;
}
