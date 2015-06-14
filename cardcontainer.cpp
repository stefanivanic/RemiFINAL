#include "cardcontainer.h"
#include "ui_cardcontainer.h"

CardContainer::CardContainer(QWidget *parent, int x, int y, int w, int h) :
    QWidget(parent),
    ui(new Ui::CardContainer),
    cards(), position(x, y), width(w), height(h)
{
    ui->setupUi(this);

    move(position); resize(w, h);

//    zasto kresuje kad se doda ovde a ne u konstruktoru Game
//    this->installEventFilter(this->parentWidget());
}

QVector<Card*> CardContainer::getCards(){
    return cards;
}

bool CardContainer::isCardTargeted(QObject *target)
{
    for(Card* c : cards)
        if(target == c)
            return true;
    return false;
}

bool CardContainer::isInArea()
{
    QPoint p = mapFromGlobal(QCursor::pos());

    if(p.x() >= 0 && p.x() <= width && p.y() >= 0 && p.y() <= height)
        return true;

    return false;
}

void CardContainer::mouseReleaseEvent(QMouseEvent *event)
{
    event->accept();

    refreshDepth();
}

void CardContainer::addCard(Card* card, bool background){

    cards.push_back(card);
    card->setImage("default", background); card->raise();
    cards.back()->move(position); cards.back()->show();


    card->installEventFilter(parentWidget());

    width += 80;
}

Card* CardContainer::getLastCard()
{
    Card* c = cards.back();

    cards.pop_back();

    width -= 80;

    return c;
}

void CardContainer::refreshDepth()
{
    for(Card* c : cards) {
        c->show();

        c->e->setOpacity(1);
        c->setGraphicsEffect(c->e);
    }
}

QString CardContainer::printCards()
{
    QString rez;

    for(Card* c : cards)
        rez.append(c->name()).append(" ");

    return rez;
}

CardContainer::~CardContainer()
{
    for(Card* c : cards)
        delete c;
    delete ui;
}

