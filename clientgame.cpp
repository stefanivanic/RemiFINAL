#include "clientgame.h"
#include "ui_game.h"

#include <QTime>
#include <QStringList>
#include <QString>



ClientGame::ClientGame(QWidget *parent, QString ip, int port) :
    Game(parent)
{
    client = new Client(this, ip, port);

    //signali od clienta
    connect(client, SIGNAL(initCards(QString)),     this,   SLOT(initializeCards(QString)));
    connect(client, SIGNAL(newMessage(QString)),    this,   SLOT(appendMessage(QString)));
    connect(client, SIGNAL(cardThrown(QString)),    this,   SLOT(addCard(QString)));
    connect(client, SIGNAL(groupThrown(QString)),   this,   SLOT(addGroupOfCards(QString)));
    connect(client, SIGNAL(groupsReturned(QString)),this,   SLOT(returnGroups(QString)));
    connect(client, SIGNAL(deckCardTaken()),        this,   SLOT(removeCardFromDeck()));
    connect(client, SIGNAL(talonCardTaken()),       this,   SLOT(removeCardFromTalon()));
    connect(client, SIGNAL(newGroupIndex(QString)), this, SLOT(changeGroup(QString)));
    connect(client, SIGNAL(talonCardRetSignal(QString)),this, SLOT(addTalonCard(QString)));
    connect(client, SIGNAL(gameEndedSignal()),      this, SLOT(playerTwoWins()));

    //signali iz game-a
    connect(this,SIGNAL(onNewMessage(QString)),        this,    SLOT(sendMessage(QString)));
    connect(this,SIGNAL(onCardThrown(QString)),        this,    SLOT(sendCard(QString)));
    connect(this,SIGNAL(onGroupOfCardsThrown(QString)),this,    SLOT(sendGroupOfCards(QString)));
    connect(this,SIGNAL(onGroupsReturned(QString)),    this,    SLOT(sendGroupIndexes(QString)));
    connect(this,SIGNAL(onDeckCardTaken()),            this,    SLOT(sendDeckSignal()));
    connect(this,SIGNAL(onTalonCardTaken()),           this,    SLOT(sendTalonSignal()));
    connect(this, SIGNAL(onGroupCardAdd(QString)),     this,    SLOT(sendGroupCards(QString)));
    connect(this,SIGNAL(talonCardReturned(QString)),   this,    SLOT(sendTalonCardRetSignal(QString)));
    connect(this,SIGNAL(gameEnded()),                  this,    SLOT(sendGameEndedSignal()));

} // END CONSTRUCTOR

void ClientGame::appendMessage(const QString &message)
{
    qDebug() << "Primio poruku: " << message;
    //ui->textEdit->append("asd");
    //ui->textEdit->append(message);
}

void ClientGame::sendMessage(const QString& message)
{
    QString data = "MESSAGE " + message;
    client->sendSignal(data);
}

void ClientGame::sendCard(const QString& card)
{
    QString data = "CARD " + card;
    client->sendSignal(data);
}

void ClientGame::addCard(const QString &card)
{
    Card* c = createCardByString(card);

    talon->addCard(c,true);
    changePlayer();
    playerTwoModCardNumber(-1);
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
    int pos_y = 180 + (table.size() / 3 ) * 130;

    CardTableContainer* cdc =
            new CardTableContainer(this, pos_x, pos_y, w1, 100);

    int i;
    for(i=0; i<list.size()-1; i++)
    {
        if(list.at(i) == "")
            continue;

        Card* c = createCardByString(list.at(i));
        cdc->addCard(c,true);
    }

    table.push_back(cdc);
    playerTwoModCardNumber(-(i-1));

    qDebug()<< "Velicina table-a " << table.size();
}

void ClientGame::sendGroupOfCards(const QString& cards)
{
    QString data = "GROUP " + cards;
    client->sendSignal(data);
}

void ClientGame::sendGroupIndexes(const QString &number)
{
    QString data = "INDEXES " + number;
    client->sendSignal(data);
}

void ClientGame::returnGroups(const QString &indexes)
{
    int n = indexes.at(0).digitValue();
    qDebug() << "Vracamo grupe " << n;

    for( int i = 0 ; i < n; i++){
        CardTableContainer* cdc = table.back();

        int size = cdc->handSize();
        int j;
        for(j = 0 ; j < size ; j++)
        {
            delete cdc->getLastCard();
        }
        playerTwoModCardNumber(j);
        table.pop_back();
    }

}

void ClientGame::removeCardFromDeck()
{
    delete deck->getLastCard();
    deck->refreshDepth();
    playerTwoModCardNumber(1);
}

void ClientGame::removeCardFromTalon()
{
    delete talon->getLastCard();
    talon->refreshDepth();
    playerTwoModCardNumber(1);
}

void ClientGame::sendDeckSignal()
{
    QString data = "DECK";
    client->sendSignal(data);
}

void ClientGame::sendTalonSignal()
{
    QString data = "TALON";
    client->sendSignal(data);
}

void ClientGame::sendGroupCards(const QString &message)
{
    QString data = "GROUPINDEX "+message;
    client->sendSignal(data);
}

void ClientGame::changeGroup(const QString &message)
{
    QStringList list = message.split(' ');

    int k=0;
    if(list[0].size()==2)
    {
        //zamenio kartu za jokera
        k=list[0].at(0).digitValue();

        //DODAJ KARTU PLAYERU 2
        playerTwoModCardNumber(1);
    }
    else
        k=list[0].toInt();

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

void ClientGame::initializeCards(const QString &cards)
{
    changePlayer();
    changePlayer();
    changePlayer();

    playerTwoModCardNumber(1);

    QStringList list = cards.split(' ');

    _Player1->deleteCards();
    _Player1->refreshDepth();

    for(int i=0; i<14; i++)
    {
        if(list[i] == "")
            continue;

        _Player1->addCard(createCardByString(list[i]),true);
    }

    _Player1->refreshDepth();

    QVector<Card*> vector;

    for(int i=14; i<list.size(); i++)
    {
        if(list[i] == "")
            continue;

        vector.push_back(createCardByString(list[i]));
    }

    qDebug() << "Dobio karte: " << cards;

  //  deck->deleteCards();
  //  deck->setNewCards(vector);

}

void ClientGame::sendTalonCardRetSignal(const QString &card)
{
    QString data = "TCARDRET " + card;
    client->sendSignal(data);
}

void ClientGame::addTalonCard(const QString &card)
{
    Card* c = createCardByString(card);

    talon->addCard(c,true);
    playerTwoModCardNumber(-1);
}

void ClientGame::sendGameEndedSignal()
{
    client->sendSignal("GAMEENDED");
}

void ClientGame::playerTwoWins()
{
    //POBEDIO PLAYER 2
    qDebug() << "Pobedio je player 2!";
}
