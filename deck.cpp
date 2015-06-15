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

Card* Deck::createCardByString(const QString& string1)
{

    int number;
    Card::Sign sign;
    Card* c;

    QString string(string1.trimmed());

    if(string.length()==2)
    {
        if(string.at(0) == 'A')
            number=1;
        else if(string.at(0) == 'K')
            number=14;
        else if(string.at(0) == 'Q')
            number=13;
        else if(string.at(0) == 'J')
            number=12;
        else
            number = string.at(0).digitValue();

        if(string.at(1) == 'P')
            sign=Card::PIK;
        else if(string.at(1) == 'K')
            sign=Card::KARO;
        else if(string.at(1) == 'T')
            sign=Card::TREF;
        else
            sign=Card::HERC;

            c = new Card(this,number,number,sign);
    }
    else if(string.at(0) == 'J')
    {
        c = new Card(this,0,0,Card::JOKER);
    }
    else{
        if(string.at(2) == 'P')
            sign=Card::PIK;
        else if(string.at(2) == 'K')
            sign=Card::KARO;
        else if(string.at(2) == 'T')
            sign=Card::TREF;
        else
            sign=Card::HERC;

        c = new Card(this,10,10,sign);
    }

    return c;
}

void Deck::deleteCards()
{
    for(int i=0; i<cards.size(); i++)
    {
        delete cards[i];
    }

    cards.clear();
}

void Deck::setNewCards(const QString& cardsList)
{
    QStringList list = cardsList.split(' ');

    for(int i=0; i<list.size(); i++)
    {
        if(list[i] == "")
            continue;

        addCard(createCardByString(list[i]),false);
        qDebug() << "dodata karta: " << list[i];
    }

    //refreshDepth();
}
