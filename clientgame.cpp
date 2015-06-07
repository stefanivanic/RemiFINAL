#include "clientgame.h"
#include "ui_game.h"

#include <QTime>
#include <QStringList>
#include <QString>



ClientGame::ClientGame(QWidget *parent) :
    Game(parent)
{
    client = new Client();

    //signali sa servera
    connect(client,SIGNAL(newMessage(QString)),this,SLOT(appendMessage(QString)));
    connect(client,SIGNAL(cardThrown(QString)),this,SLOT(addCard(QString)));
    connect(client,SIGNAL(groupThrown(QString)),this,SLOT(addGroupOfCards(QString)));
    connect(client,SIGNAL(groupsReturned(QString)),this,SLOT(returnGroups(QString)));
    connect(client,SIGNAL(cardTaken()),this,SLOT(removeCardFromDeck()));

    //signali iz game-a
    connect(this,SIGNAL(onCardThrown(QString)),this,SLOT(sendCard(QString)));
    connect(this,SIGNAL(onGroupOfCardsThrown(QString)),this,SLOT(sendGroupOfCards(QString)));
    connect(this,SIGNAL(onGroupsReturned(QString)),this,SLOT(sendGroupIndexes(QString)));
    connect(this,SIGNAL(onCardTaken()), this, SLOT(sendDeckSignal()));

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

void ClientGame::sendCard(const QString& card)
{
    client->sendCard(card);
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

void ClientGame::sendGroupOfCards(const QString& cards)
{
    client->sendGroupOfCards(cards);
}

void ClientGame::sendGroupIndexes(const QString &number)
{
    client->sendGroupIndexes(number);
}

void ClientGame::returnGroups(const QString &indexes)
{
    int n = indexes.at(0).digitValue();
    qDebug() << "Vracamo grupe " << n;

    for( int i = 0 ; i < n; i++){
        CardTableContainer* cdc = table.back();

        int size = cdc->handSize();
        for(int j = 0 ; j < size ; j++)
            cdc->removeLastCard();

        //TREBALO BI DA REFRESUJE DEO GDE JE UZEO KARTE
        qDebug() << "ispisuje karte koje su ostale...";
        cdc->printCards();
        table.pop_back();
    }

}

void ClientGame::removeCardFromDeck()
{
    deck->removeLastCard();
}

void ClientGame::sendDeckSignal()
{
    client->sendDeckSignal();
}


