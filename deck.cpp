#include "deck.h"
#include "ui_deck.h"



Deck::Deck(QWidget *parent, int x, int y, int w, int h)
    : CardContainer(parent, x, y, w, h), chosenCards(false)
{
    QVector<QString> nul;
    initializeDeck( nul );
    shuffleDeck   ();
}

Deck::Deck(QWidget *parent, int x, int y, int w, int h, QVector<QString> cardNames)
    : CardContainer(parent, x, y, w, h), chosenCards(true)
{
    initializeDeck(cardNames);
   // shuffleDeck   ();
}


void Deck::initializeDeck(QVector<QString> cardNames)
{
    for(int i=0; i<2; i++){
        for(int j=1; j<15; j++){
            if(j==11) continue;
            addCard(new Card(parentWidget(), j,j, Card::KARO), false);
            addCard(new Card(parentWidget(), j,j, Card::TREF), false);
            addCard(new Card(parentWidget(), j,j, Card::PIK) , false);
            addCard(new Card(parentWidget(), j,j, Card::HERC), false);
        }
    }
    for(int i=0; i<4; i++)
        addCard(new Card(parentWidget(), 0,0, Card::JOKER), false);

    if(chosenCards) {
        for(int i=0; i<cardNames.size(); i++) {
            for(int j=0; j < cards.size() ; j++) {
                if(cardNames[i] == cards[j]->name()) {
        /*
                    Card* c = cards[j];
                    cards.erase(cards.begin() + j);
                    cards.append(c);
*/
                    std::swap(cards[j], cards[cards.size() - i - 1]);

                    break;
                }
            }
        }
//        qDebug() << printCards();
    }

}

void Deck::shuffleDeck()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle (cards.begin(), cards.end(), std::default_random_engine(seed));

    refreshDepth();
}
