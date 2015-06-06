#include "servergame.h"
#include "ui_game.h"
#include "card.h"

#include <QTime>
#include <QStringList>


ServerGame::ServerGame(QWidget *parent) :
    Game(parent)
{
    server = new Server();
}

Card* ServerGame::createCardByString(const QString& string1)
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

void ServerGame::appendMessage(const QString &message)
{
    ui->textEdit->append(message);
}

void ServerGame::on_lineEdit_returnPressed()
{
    ui->textEdit->append(ui->lineEdit->text());

    QString s(ui->lineEdit->text());
    server->sendMessage(s);
}

void ServerGame::onCardThrown()
{
    server->sendCard(_Player1->getTempCard()->name());
}

void ServerGame::addCard(const QString &card)
{
    Card* c = createCardByString(card);

    talon->addCard(c,true);
}

void ServerGame::addGroupOfCards(const QString &cards)
{

    QStringList list = cards.split(' ');

    int w1 = list.size() * 20;
    int pos_x = std::accumulate(table.begin() + table.size() / 3 * 3,
                                table.end(),
                                200,
                                [](const int& a, CardTableContainer* cdc)
                                    { return a + cdc->getContainerWidth(); } );
    int pos_y = 150 + (table.size() / 3 ) * 100;

    CardTableContainer* cdc =
            new CardTableContainer(this, pos_x, pos_y, w1, 100);


    for(int i=0; i<list.size()-1; i++)
    {
        Card* c = createCardByString(list.at(i));
        cdc->addCard(c,true);
    }

    table.append(cdc);
}

void ServerGame::onGroupOfCardsThrown()
{
    QString cards = "";

    for(int i=0; i<_Player1->group->getCards().size(); i++)
        cards.append(_Player1->group->getCards()[i]->name()+" ");

    qDebug() << cards << " <--- Karte";

    server->sendGroupOfCards(cards);
}

