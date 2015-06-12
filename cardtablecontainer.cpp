#include "cardtablecontainer.h"
#include "ui_cardtablecontainer.h"

CardTableContainer::CardTableContainer(QWidget *parent, int x, int y, int w, int h)
    : PlayerContainer(parent, x, y, w, h)
{}

void CardTableContainer::print()
{
    qDebug() << printCards();
}

void CardTableContainer::addCards(QVector<Card*> _cards)
{
    for(Card* c : _cards) {
        c->move(position.x() + PlayerContainer::cards.size() * cardDistance,
                position.y());
        PlayerContainer::cards.push_back(c);
        c->raise();
    }
}

void CardTableContainer::addCard(Card *card, bool background)
{
    resize(width + 100, height);
    PlayerContainer::addCard(card, background);
}

void CardTableContainer::moveRight() {
//    qDebug() << " pozicija x : " << position.x();

    position.setX(position.x() + cardDistance);
    refreshCardsPosition();
}

int CardTableContainer::getContainerWidth()
{
    // 80 je otprilike sirina karte
    return (PlayerContainer::cards.size() - 1) * cardDistance + 100;
}
