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
    void sendMessage(const QString& message);
    void sendCard(const QString& card);
    void sendGroupOfCards(const QString& cards);
    void sendGroupIndexes(const QString& number);
    void sendDeckSignal();

public slots:
    void appendMessage(const QString& message);
    void addCard(const QString& card);
    void addGroupOfCards(const QString& cards);
    void returnGroups(const QString& indexes);
    void removeCardFromDeck();

private:
    Server* server;
};

#endif // SERVERGAME_H
