#include "servergame.h"
#include "ui_game.h"
#include "card.h"

#include <QTime>
#include <QStringList>


ServerGame::ServerGame(QWidget *parent) :
    Game(parent)
{
    server = new Server();

    //signali sa servera
    connect(server, SIGNAL(newMessage(QString)),    this,   SLOT(appendMessage(QString)));
    connect(server, SIGNAL(cardThrown(QString)),    this,   SLOT(addCard(QString)));
    connect(server, SIGNAL(groupThrown(QString)),   this,   SLOT(addGroupOfCards(QString)));
    connect(server, SIGNAL(groupsReturned(QString)),this,   SLOT(returnGroups(QString)));
    connect(server, SIGNAL(deckCardTaken()),        this,   SLOT(removeCardFromDeck()));
    connect(server, SIGNAL(talonCardTaken()),       this,   SLOT(removeCardFromTalon()));
    connect(server, SIGNAL(newGroupIndex(QString)), this, SLOT(changeGroup(QString)));

    //signali iz game-a
    connect(this,   SIGNAL(onNewMessage(QString)),        this, SLOT(sendMessage(QString)));
    connect(this,   SIGNAL(onCardThrown(QString)),        this, SLOT(sendCard(QString)));
    connect(this,   SIGNAL(onGroupOfCardsThrown(QString)),this, SLOT(sendGroupOfCards(QString)));
    connect(this,   SIGNAL(onGroupsReturned(QString)),    this, SLOT(sendGroupIndexes(QString)));
    connect(this,   SIGNAL(onDeckCardTaken()),            this, SLOT(sendDeckSignal()));
    connect(this,   SIGNAL(onTalonCardTaken()),           this, SLOT(sendTalonSignal()));
    connect(this, SIGNAL(onGroupCardAdd(QString)),        this, SLOT(sendGroupCards(QString)));

} // END CONSTRUCTOR

void ServerGame::appendMessage(const QString &message)
{
    ui->textEdit->append(message);
}

void ServerGame::sendMessage(const QString &message)
{
    server->sendMessage(message);
}

void ServerGame::sendCard(const QString& card)
{
    qDebug() << "Stigo do dela da posalje kartu -> " + card;
    server->sendCard(card);
}

void ServerGame::addCard(const QString &card)
{
    Card* c = createCardByString(card);

    talon->addCard(c,true);
    playerOneOnMove = true;
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
        if(list.at(i) == "")
            continue;

        Card* c = createCardByString(list.at(i));
        cdc->addCard(c,true);

        qDebug() << "Dodajem kartu:" + list.at(i);
    }

    table.append(cdc);
}

void ServerGame::sendGroupOfCards(const QString& cards)
{
    server->sendGroupOfCards(cards);
}

void ServerGame::sendGroupIndexes(const QString &number)
{
    server->sendGroupIndexes(number);
}

void ServerGame::returnGroups(const QString &indexes)
{
    int n = indexes.at(0).digitValue();
    qDebug() << "Vracamo grupe " << n;

    for( int i = 0 ; i < n; i++){
        CardTableContainer* cdc = table.back();

        int size = cdc->handSize();
        for(int j = 0 ; j < size ; j++)
            delete cdc->getLastCard();

        table.pop_back();
    }

}

void ServerGame::removeCardFromDeck()
{
    delete deck->getLastCard();
    deck->refreshDepth();
}

void ServerGame::removeCardFromTalon()
{
    delete talon->getLastCard();
    talon->refreshDepth();
}

void ServerGame::sendDeckSignal()
{
    delete deck->getLastCard();
    deck->refreshDepth();
}

void ServerGame::sendTalonSignal()
{
    server->sendTalonSignal();
}

void ServerGame::sendGroupCards(const QString &message)
{
    server->sendGroupCards(message);
}

void ServerGame::changeGroup(const QString &message)
{
    QStringList list = message.split(' ');

    int k = list[0].toInt();

    CardTableContainer* cdc = NULL;
    cdc = table[k];

    int size = cdc->handSize();
    for(int j = 0 ; j < size ; j++)
        delete cdc->getLastCard();

    for(int i=1; i<list.size()-1; i++)
    {
        if(list[i] == "")
            continue;

        Card* c = createCardByString(list[i]);
        cdc->addCard(c,true);
    }

    int granica = (k/3 +1) * 3;
    qDebug() << "granica : " << granica;
    for(int i = k + 1; i < granica && i < table.size() ; i++){
        table[i]->moveRight();
    }

    cdc->refreshDepth();
    cdc->refreshCardsPosition();
}
