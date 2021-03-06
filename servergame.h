#ifndef SERVERGAME_H
#define SERVERGAME_H


#include <QMainWindow>
#include <QMessageBox>

#include "game.h"
#include "playercontainer.h"
#include "card.h"
#include "selecttheme.h"
#include "talon.h"
#include "deck.h"
#include "cardtablecontainer.h"
#include "choosecards.h"
#include "ui_game.h"
#include "server.h"
#include "client.h"

class ServerGame :public Game
{
    Q_OBJECT

public:
    explicit ServerGame(QWidget *parent = 0);

private slots:
    void clientConnected();
    void sendMessage(const QString& message);
    void sendCard(const QString& card);
    void sendGroupOfCards(const QString& cards);
    void sendGroupIndexes(const QString& number);
    void sendDeckSignal();
    void sendTalonSignal();
    void sendGroupCards(const QString& message);
    void sendTalonCardRetSignal(const QString& card);

public slots:
    void appendMessage(const QString& message);
    void addCard(const QString& card);
    void addGroupOfCards(const QString& cards);
    void returnGroups(const QString& indexes);
    void removeCardFromDeck();
    void removeCardFromTalon();
    void changeGroup(const QString& message);
    void addTalonCard(const QString& card);
    void clientLeft();

private:
    Server* server;
    QLabel* ipPortLabel;
    void playerTwoWins();
};

#endif // SERVERGAME_H
