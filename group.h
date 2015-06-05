#ifndef GROUP_H
#define GROUP_H

#include <QVector>
#include <QDebug>

#include "sign.h"
#include "card.h"

class Group
{
public:
    Group();

    bool addCard(Card* card);
    bool    removeCard(Card* card);
    int     isCorrectGroup();
    void    clearGroup();
    void    sortGroup();
    void    correctValues();

    QVector<Card*> getCards() const { return cards; }

private:
    QVector<Card*> cards;
    unsigned value;
};

#endif // GROUP_H
