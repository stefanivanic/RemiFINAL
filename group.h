#ifndef GROUP_H
#define GROUP_H

#include <QVector>
#include <QDebug>

#include "card.h"

class Group
{
public:
    Group();

    enum type { SAME_SIGN, SAME_NUMBER };

    bool    addCard(Card* card);
    bool    removeCard(Card* card);
    int     isCorrectGroup(bool shuffle);
    void    clearGroup();
    void    sortGroup();
    void    correctValues();

    int type();

    QVector<Card*> getCards() const { return cards; }

private:
    QVector<Card*> cards;
    unsigned value;
};

#endif // GROUP_H
