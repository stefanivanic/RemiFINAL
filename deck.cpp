#include "deck.h"
#include "ui_deck.h"

Deck::Deck(QWidget *parent, int x, int y, int w, int h)
    : CardContainer(parent, x, y, w, h)
{
    initializeDeck();
    shuffleDeck   ();
}

void Deck::initializeDeck()
{
    for(int i=0; i<2; i++){
        for(int j=1; j<15; j++){
            if(j==11) continue;
            addCard(new Card(parentWidget(), j,j, KARO), false);
            addCard(new Card(parentWidget(), j,j, TREF), false);
            addCard(new Card(parentWidget(), j,j, PIK) , false);
            addCard(new Card(parentWidget(), j,j, HERC), false);
        }
    }
    for(int i=0; i<4; i++)
        addCard(new Card(parentWidget(), 0,0, JOKER), false);
}

void Deck::shuffleDeck()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle (cards.begin(), cards.end(), std::default_random_engine(seed));

    refreshDepth();
}
