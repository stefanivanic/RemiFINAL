#include "clientgame.h"
#include "ui_game.h"

#include <QTime>
#include <QStringList>
#include <QString>



ClientGame::ClientGame(QWidget *parent) :
    Game(parent)
{
    client = new Client();

} // END CONSTRUCTOR

void ClientGame::appendMessage(const QString &message)
{
    ui->textEdit->append(message);
}

void ClientGame::on_lineEdit_returnPressed()
{
    QString s(ui->lineEdit->text());
    client->sendMessage(s);
}

void ClientGame::onCardThrown()
{
    client->sendCard(_Player1->getTempCard()->name());
}

void ClientGame::addCard(const QString &card)
{
    Card* c = createCardByString(card);

    talon->addCard(c,true);
}

void ClientGame::addGroupOfCards(const QString &cards)
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

void ClientGame::onGroupOfCardsThrown()
{
    QString cards = "";

    for(int i=0; i<_Player1->group->getCards().size(); i++)
        cards.append(_Player1->group->getCards()[i]->name()+" ");

    qDebug() << cards << " <--- Karte";

    client->sendGroupOfCards(cards);
}

