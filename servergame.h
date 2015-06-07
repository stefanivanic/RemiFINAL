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
    void on_lineEdit_returnPressed();
    void sendCard(const QString& card);
    void sendGroupOfCards(const QString& cards);

public slots:
    void appendMessage(const QString& message);
    void addCard(const QString& card);
    void addGroupOfCards(const QString& cards);

private:
    Server* server;
};

#endif // SERVERGAME_H
