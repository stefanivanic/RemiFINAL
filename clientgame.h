#ifndef CLIENTGAME_H
#define CLIENTGAME_H


#include <QMainWindow>
#include <QMessageBox>

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
#include "game.h"


class ClientGame : public Game
{
    Q_OBJECT

public:
    explicit ClientGame(QWidget *parent = 0, QString ip = "", int port = 0);

private slots:
    void sendMessage(const QString& message);
    void sendCard(const QString& card);
    void sendGroupOfCards(const QString& cards);
    void sendGroupIndexes(const QString& number);
    void sendDeckSignal();
    void sendTalonSignal();
    void sendGroupCards(const QString& message);

public slots:
    void appendMessage(const QString& message);
    void addCard(const QString& card);
    void addGroupOfCards(const QString& cards);
    void returnGroups(const QString& indexes);
    void removeCardFromDeck();
    void removeCardFromTalon();
    void changeGroup(const QString& message);
    void initializeCards(const QString& cards);

private:
    Client* client;

    Ui::Game *ui;
};
#endif // CLIENTGAME_H
