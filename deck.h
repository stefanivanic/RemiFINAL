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

private:
    void shuffleDeck();
    void initializeDeck();
};

#endif // DECK_H
