#ifndef DECK_H
#define DECK_H

#include "cardcontainer.h"

namespace Ui {
class Deck;
}

class Deck : public CardContainer
{
    Q_OBJECT

public:
    Deck(QWidget *parent, int x, int y, int w, int h);
    Deck(QWidget *parent, int x, int y, int w, int h, QVector<QString> cardNames);


    void deleteCards();
    void setNewCards(QVector<Card*> cards);
private:
    void shuffleDeck();
    void initializeDeck(QVector<QString> cardNames);

    bool chosenCards;
};

#endif // DECK_H
