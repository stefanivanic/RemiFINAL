#ifndef SERVERGAME_H
#define SERVERGAME_H


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



class ServerGame : public QMainWindow,private Ui::Game
{
    Q_OBJECT

public:
    explicit ServerGame(QWidget *parent = 0);
    ~ServerGame();

    void playerToTalon();

    //void delay(double seconds, QString message);

    enum player { PLAYER1, PLAYER2};

    static int const EXIT_CODE_REBOOT = -666;

    Card* createCardByString(const QString& string);

private slots:
    void on_actionSelect_theme_triggered();
    void on_throwGroup_clicked();
    void changeTempPosText();
    void changePlayer();
    void showOnThrowButton();
    void hideOnThrowButton();
    void slotReboot();
    void on_undoGroup_clicked();

    void on_actionChoose_cards_triggered();
    void on_lineEdit_returnPressed();

public slots:
    void appendMessage(const QString& message);

private:
    Server* server;


    Ui::Game *ui;

    QString theme;

    PlayerContainer *_Player1;

    Talon* talon;
    Deck*   deck;

    ChooseCards* chooseCards;

    QVector<CardTableContainer*> table;

    bool playerOneOnMove;
    bool playerTookCard;
    bool goodOpening;
    bool playerTookCardFromTalon;
    bool firstTime;
    int groupsThrown;
    int groupValue;

    void initSnS();

    void setBackgroundColor();

    SelectTheme *selectTheme;
    QMessageBox::StandardButton endGameDialog;

    bool endGameFlag;

    bool eventFilter(QObject* target, QEvent* event);
};

#endif // SERVERGAME_H