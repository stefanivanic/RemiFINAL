#include "servergame.h"
#include "ui_game.h"
#include "card.h"

#include <QTime>
#include <QStringList>


ServerGame::ServerGame(QWidget *parent) :
    Game(parent)
{
    server = new Server();

    ipPortLabel = new QLabel(this);
    ipPortLabel->move(300, 280);
    ipPortLabel->setText(server->getIp()+ ":" + QString::number(server->getPort()));
    ipPortLabel->resize(400, 50);
    ipPortLabel->setStyleSheet(QStringLiteral("font-size: 40px"));

    //signali sa servera
    connect(server, SIGNAL(newClient()),        this, SLOT(clientConnected()));
    connect(server, SIGNAL(newMessage(QString)),    this,   SLOT(appendMessage(QString)));
    connect(server, SIGNAL(cardThrown(QString)),    this,   SLOT(addCard(QString)));
    connect(server, SIGNAL(groupThrown(QString)),   this,   SLOT(addGroupOfCards(QString)));
    connect(server, SIGNAL(groupsReturned(QString)),this,   SLOT(returnGroups(QString)));
    connect(server, SIGNAL(deckCardTaken()),        this,   SLOT(removeCardFromDeck()));
    connect(server, SIGNAL(talonCardTaken()),       this,   SLOT(removeCardFromTalon()));
    connect(server, SIGNAL(newGroupIndex(QString)), this, SLOT(changeGroup(QString)));
    connect(server, SIGNAL(talonCardRetSignal(QString)),this, SLOT(addTalonCard(QString)));
    connect(server, SIGNAL(gameEndedSignal()),      this, SLOT(playerTwoWins()));

    //signali iz game-a
    connect(this,   SIGNAL(onNewMessage(QString)),        this, SLOT(sendMessage(QString)));
    connect(this,   SIGNAL(onCardThrown(QString)),        this, SLOT(sendCard(QString)));
    connect(this,   SIGNAL(onGroupOfCardsThrown(QString)),this, SLOT(sendGroupOfCards(QString)));
    connect(this,   SIGNAL(onGroupsReturned(QString)),    this, SLOT(sendGroupIndexes(QString)));
    connect(this,   SIGNAL(onDeckCardTaken()),            this, SLOT(sendDeckSignal()));
    connect(this,   SIGNAL(onTalonCardTaken()),           this, SLOT(sendTalonSignal()));
    connect(this, SIGNAL(onGroupCardAdd(QString)),        this, SLOT(sendGroupCards(QString)));
    connect(this, SIGNAL(talonCardReturned(QString)),     this, SLOT(sendTalonCardRetSignal(QString)));
    connect(this, SIGNAL(gameEnded()),                    this, SLOT(sendGameEndedSignal()));

    playerTwoModCardNumber(0);
} // END CONSTRUCTOR

void ServerGame::appendMessage(const QString &message)
{
    ui->textEdit->append(message);
}

void ServerGame::sendMessage(const QString &message)
{
    QString data = "MESSAGE " + message;
    server->sendSignal(data);
}

void ServerGame::sendCard(const QString& card)
{
    QString data = "CARD " + card;
    server->sendSignal(data);
}

void ServerGame::addCard(const QString &card)
{
    Card* c = createCardByString(card);

    talon->addCard(c,true);
    changePlayer();
    playerTwoModCardNumber(-1);
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
    int pos_y = 180 + (table.size() / 3 ) * 130;

    CardTableContainer* cdc =
            new CardTableContainer(this, pos_x, pos_y, w1, 100);

    int i;
    QVector<Card*> vector;
    for(i=0; i<list.size()-1; i++)
    {
        if(list.at(i) == "")
            continue;

        Card* c = createCardByString(list.at(i));

        QString theme = "2";
        QSize size = c->setImage(theme, true);

        c->resize(size.width(), size.height());

        vector.push_back(c);

        qDebug() << "Dodajem kartu:" + list.at(i);
    }

    cdc->addCards(vector);
    cdc->refreshDepth();

    table.push_back(cdc);
    playerTwoModCardNumber(-(i-1));

    qDebug() << "Velicina tabel-a " << table.size();
}

void ServerGame::sendGroupOfCards(const QString& cards)
{
    QString data = "GROUP " + cards;
    server->sendSignal(data);
}

void ServerGame::sendGroupIndexes(const QString &number)
{
    QString data = "INDEXES " + number;
    server->sendSignal(data);
}

void ServerGame::returnGroups(const QString &indexes)
{
    int n = indexes.at(0).digitValue();
    qDebug() << "Vracamo grupe " << n;

    for( int i = 0 ; i < n; i++){
        CardTableContainer* cdc = table.back();

        int size = cdc->handSize();
        int j;
        for(j = 0 ; j < size ; j++)
            delete cdc->getLastCard();

        playerTwoModCardNumber(j-1);
        table.pop_back();
    }

}

void ServerGame::removeCardFromDeck()
{
    delete deck->getLastCard();
    deck->refreshDepth();
    playerTwoModCardNumber(1);
}

void ServerGame::removeCardFromTalon()
{
    delete talon->getLastCard();
    talon->refreshDepth();
    playerTwoModCardNumber(1);
}

void ServerGame::sendDeckSignal()
{
    QString data = "DECK";
    server->sendSignal(data);
}

void ServerGame::sendTalonSignal()
{
    QString data = "TALON";
    server->sendSignal(data);
}

void ServerGame::sendGroupCards(const QString &message)
{
    QString data = "GROUPINDEX "+message;
    server->sendSignal(data);
}

void ServerGame::changeGroup(const QString &message)
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
    {
        k=list[0].toInt();
        playerTwoModCardNumber(-1);
    }

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

void ServerGame::clientConnected()
{
    delete ipPortLabel;

    playerTwoModCardNumber(14);

    QString cards("");

    for(int i=0; i<deck->getCards().size(); i++)
    {
        cards.append(deck->getCards()[i]->name());
        cards.append(" ");
    }

    qDebug() << "Karte :" << cards;

    server->sendSignal("INITCARDS "+cards);
}

void ServerGame::sendTalonCardRetSignal(const QString &card)
{
    QString data = "TCARDRET " + card;
    server->sendSignal(data);
}

void ServerGame::addTalonCard(const QString &card)
{
    Card* c = createCardByString(card);

    talon->addCard(c,true);
    playerTwoModCardNumber(-1);
}

void ServerGame::sendGameEndedSignal()
{
    server->sendSignal("GAMEENDED");
}

void ServerGame::playerTwoWins()
{
    qDebug() << "Pobedio je player 2!";
}
