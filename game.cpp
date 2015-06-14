#include "game.h"
#include "ui_game.h"

#include <QTime>
#include <QStringList>
#include <QMediaPlayer>

Game::Game(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::Game),
    theme("default"), playerOneOnMove(true), playerTookCard(true),
    goodOpening(false), playerTookCardFromTalon(0),
    firstTime(true), groupsThrown(0), groupValue(0),
    endGameFlag(false)
{
    ui->setupUi(this);
  /*  ui->centralWidget->setStyleSheet(QStringLiteral("border-image: url(./slike/2/dark_wood.jpg);"));
    ui->label->setStyleSheet(QStringLiteral("border-image: url(./slike/2/white.jpg);"));
    ui->onMoveLabel->setStyleSheet(QStringLiteral("border-image: url(./slike/2/white.jpg);"));
    ui->errorLogger->setStyleSheet(QStringLiteral("border-image: url(./slike/2/white.jpg);"));
    ui->groupValue->setStyleSheet(QStringLiteral("border-image: url(./slike/2/white.jpg);"));
    ui->textEdit->setStyleSheet(QStringLiteral("border-image: url();"));
    ui->lineEdit->setStyleSheet(QStringLiteral("border-image: url(./slike/2/white.jpg);"));
*/ //   ui->throwGroup->setStyleSheet(QStringLiteral("border-image: url(./slike/Teme/2_vratigrupu.jpg);"));
 /*   ui->undoGroup->setStyleSheet(QStringLiteral("border-image: url();"));
*/
    ui->throwGroup->hide(); ui->undoGroup->hide(); ui->undoTookTalonCard->hide();

    _Player1 = new PlayerContainer(this, 300, 450, 350, 100);

    // napravi kontejner za playera 2 ovo ne
    // moze ovako da ostane jer mora dinamicki da se menja
    // broj karata koje protivnik ima u ruci

    chooseCards = new ChooseCards(this);

    deck = new Deck(this, 10, 250, 70, 100); // init i shuffle
    talon = new Talon(this, 100, 250, 70, 100);

    _Player1->installEventFilter(this);

    talon->installEventFilter(this);
    deck->installEventFilter(this);

    // inicijalizacija signal-slotova
    initSnS();

    // podela karata
    for(int i=0; i<15; i++)
        _Player1->addCard(deck->getLastCard(), true);
    // u add card vise ne mora da se prosledjuje bool

    /*
    QMediaPlayer *song = new QMediaPlayer();
    song->setMedia(QUrl("qrc:/music/Calle_Real-Ya_lo_se.mp3"));
    song->play();
    */
} // END CONSTRUCTOR

void Game::initSnS()
{
    // monitoring glega za tempCardPosition
    connect( _Player1, SIGNAL(onPositionChange()),
                 this, SLOT(changeTempPosText()));
    // bacili kartu => pomeraju se flegovi, tekst itd
    connect( _Player1, SIGNAL(onThrowCard()),
                 this, SLOT(changePlayer()));
    // aktiviramo grupu => prikaz dugmeta za izbacivanje grupe
    connect( _Player1, SIGNAL(onAddingCardtoGroup(bool)),
                 this, SLOT(showOnThrowButton(bool)));
    // nema grupe => nema dugmeta
    connect( _Player1, SIGNAL(onEmptyGroup(bool)),
                 this, SLOT(hideOnThrowButton(bool)));
    // za restart aplikacije
    connect( ui->menuBarRestartGame, SIGNAL(triggered()),
              this, SLOT(slotReboot()));
    // saljemo info o izabranim kartama iz jednog u main window
    connect( chooseCards, SIGNAL(cardsPreorderd(QVector<QString>)),
                    this, SLOT(cardsPreordered(QVector<QString>)));

}

void Game::playerToTalon()
{
    // ovo je trentuno
    playerOneOnMove = !playerOneOnMove;

    talon->addCard(_Player1->getTempCard(), true);
    _Player1->removeCard();

    // player je pobedio
    if(_Player1->handSize() == 0) {
        endGameDialog = QMessageBox::question(this, "Restart",
                                        " Pobeda! Nova igra?",
                                        QMessageBox::Yes|QMessageBox::No);

        if (endGameDialog == QMessageBox::Yes)  emit slotReboot();
        else QApplication::quit();

        endGameFlag = true;
    }

    playerTookCard = false; // ovo ovde ili u changeOnMoveTExt()
}

void Game::on_undoGroup_clicked()
{
    for( int i = 0 ; i < groupsThrown; i++){
        CardTableContainer* cdc = table.back();

        int size = cdc->handSize();
        for(int j = 0 ; j < size ; j++)
            _Player1->addCard(cdc->getLastCard(), true);

        table.pop_back();
    }

    //DEO ZA MREZU!!!
    emit onGroupsReturned(QString::number(groupsThrown));

    groupsThrown = 0;
    groupValue = 0;

    ui->undoGroup->hide();

    qDebug() << "kliknuto";

}

void Game::changeTempPosText()
{
    QString s("Player1 : tempCardPosition : ");
    s.append( QString::number(_Player1->getTempCardPos()) );
    ui->label->setText(s);
}

// postavljaju se flegovi i ispisuju se loggeri
void Game::changePlayer()
{
    // .........................
    // privremeno, za debug !!!!
    // .........................
    playerOneOnMove = !playerOneOnMove;

    groupsThrown = 0;
    groupValue   = 0;

    ui->errorLogger->setText("error logger.");
    ui->groupValue->setText("group value : 0");

    QString s("on move : ");
    QString s1 = playerOneOnMove ? "player1" : "player2" ;
    ui->onMoveLabel->setText(s.append(s1));
}
/*
void Game::delay(double seconds, QString message)
{
    ui->aiLogger->setText(message);

    QTime dieTime= QTime::currentTime().addSecs(seconds);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    ui->aiLogger->setText("CHILLING");
}
*/
void Game::on_throwGroup_clicked()
{

    if(!playerTookCard) {
        ui->errorLogger->setText("PRVO UZMITEW KARTU");
        return;
    }
    int retValue = _Player1->group->isCorrectGroup(true);
    if( retValue < 0) {
        switch( retValue ) {
        case -1 : ui->errorLogger->setText("-1 : manje od 3 karte!"); break;
        case -2 : ui->errorLogger->setText("-2 : vise djokera!"); break;
        case -3 : ui->errorLogger->setText("-3 : niti su istog znaka niti su svi razlicitog"); break;
        case -4 : ui->errorLogger->setText("-4 : razlicitog znaka ali i razlicite vr"); break;
        case -5 : ui->errorLogger->setText("-5 : istog znaka ali brojevi nisu dobri"); break;
        default : ui->errorLogger->setText("nepoznaa greska" + QString::number(retValue)); break;
        }
        return;
    }
    if(_Player1->group->getCards().size() == (int)_Player1->handSize()) {
        ui->errorLogger->setText("mora da vam ostane bar 1 karta");
        return;
    }
//      ui->errorLogger->setText("");
    groupValue += retValue;
    ui->groupValue->setText("group value :" + QString::number(groupValue));

    int w1 = _Player1->group->getCards().size() * 20;
    int pos_x = std::accumulate(table.begin() + table.size() / 3 * 3,
                                table.end(),
                                200,
                                [](const int& a, CardTableContainer* cdc)
                                    { return a + cdc->getContainerWidth(); } );
    int pos_y = 180 + (table.size() / 3 ) * 130;

    CardTableContainer* cdc =
            new CardTableContainer(this, pos_x, pos_y, w1, 100);


    //DEO ZA MREZU!!!
    QString cards = "";

    for(int i=0; i<_Player1->group->getCards().size(); i++)
       cards.append(_Player1->group->getCards()[i]->name()+" ");

    emit onGroupOfCardsThrown(cards);
    ui->undoGroup->show();

    // i dodajemo u grupu i brisemo iz playera
    cdc->addCards(_Player1->group->getCards());
    _Player1->deleteCardsFromGroup();

    groupsThrown++;

    table.push_back(cdc);

    if(groupValue > 51) _Player1->alreadyOpened = true;
}

bool Game::eventFilter(QObject* target, QEvent* event)
{
    if(event->type() == QEvent::MouseButtonPress ||
        event->type() == QEvent::MouseButtonRelease||
        event->type() == QEvent::MouseMove) {

        QMouseEvent* m_event = static_cast<QMouseEvent*>(event);

        if(_Player1->isCardTargeted(target)) {

            bool isInTable = std::count_if(table.begin(), table.end(),
                                           [](CardTableContainer* cdc){return cdc->isInArea(); });

            if(!talon->isInArea() && !isInTable) {
                _Player1->resolveMouseEvent(m_event);
            }

            int tableContainterPosition;
            if(isInTable) {
                CardTableContainer* cdc = NULL;
                int k;
                for(k=0; k<table.size(); k++) {
                    if(table[k]->isInArea()) {
                        cdc = table[k];
                        tableContainterPosition = k;
                        break;
                    }
                }
                if(event->type() == QEvent::MouseButtonRelease) {
                    if( cdc != nullptr) {

                        if( _Player1->getCards().size() == 1) {
                            ui->errorLogger->setText("Ne mozete praznih ruku");
                            _Player1->mouseReleaseEvent(m_event); event->ignore(); return true;
                        }

                        Group g;
                        for(int i=0; i<cdc->CardContainer::getCards().size(); i++)
                            g.addCard(cdc->CardContainer::getCards()[i]);

                        g.addCard(_Player1->getTempCard());

                        int value = g.isCorrectGroup(false); //ovde mi izmeni vrednost jokera
//                        qDebug() << "isCorrectGroup() vraca : " << value;

                        if(value > 0){

                            qDebug() << "samo ispis";
                            for(Card* c : g.getCards())
                                qDebug() << c->name();

                            int jokerFlag = -1;
                            int tempCardValue = _Player1->getTempCard()->getValue();

//                            qDebug() << "temp card value : " << tempCardValue;


                            int i;
                            for(i=0; i < g.getCards().size(); i++)
                                if(g.getCards()[i]->getSign() == Card::JOKER)
                                {
                                    jokerFlag = i;
                                    qDebug() << "Jokerflag: " << jokerFlag << "vrednost: " << g.getCards()[jokerFlag]->getValue();
                                    break;
                                }

                            //qDebug() << "joker value : " << g.getCards()[jokerFlag]->getValue();

                            // .........................................
                            // BEGIN PROVERE ZA UBACIVANJE KARTE U GRUPU
                            // .........................................

                            _Player1->removeCard();
                            cdc->removeCards();

                            if(jokerFlag != -1 && _Player1->getTempCard()->getSign() != Card::JOKER) {
                                if(g.type() == Group::SAME_SIGN)
                                {
                                    _Player1->addCard(g.getCards()[jokerFlag], true);
                                    cdc->addCards(g.getCards().mid(0, g.getCards().size()-1));

                                    qDebug() << "Karta zamenjena za jokera! SAME SIGN";
                                }
                                if(g.type() == Group::SAME_NUMBER)
                                {
                                    // VEC SU SVI ZNAKOVI ISTOG BROJA,
                                    // i dodajemo kartu i uzimamo dzokera
                                    if(g.getCards().size() == 5) {
                                        _Player1->addCard(g.getCards()[jokerFlag], true);
                                        cdc->addCards(g.getCards().mid(0, g.getCards().size()-1));
                                    }

                                    // samo dodajemo kartu, i pomeramo sve ostale cdc udesno
                                    else {
                                        cdc->addCards(g.getCards().mid(0, g.getCards().size()));

                                        int granica = (tableContainterPosition/3 + 1) * 3;
                                        qDebug() << "granica : " << granica;
                                        for(int i = tableContainterPosition + 1 ; i < granica && i < table.size() ; i++){
                                            table[i]->moveRight();
                                        }
                                    }

                                    qDebug() << "Karta zamenjena za jokera! SAME NUMBER";
                                }
                            }
                            else {
                                cdc->addCards(g.getCards().mid(0, g.getCards().size()));

                                //DEO ZA MREZU!
                                QString message("");

                                //iterator za grupu
                                message.append(QString::number(k));
                                message.append(" ");

                                for(int i=0; i<g.getCards().size(); i++){
                                      message.append(g.getCards()[i]->name());
                                      message.append(" ");
                                }

                                emit onGroupCardAdd(message);
                                qDebug() << "Poslat signal za dodavanje na grupu! " << message;
                                //KRAJ DELA ZA MREZU!

                                int granica = (tableContainterPosition/3 +1) * 3;
                                qDebug() << "granica : " << granica;
                                for(int i = tableContainterPosition + 1; i < granica && i < table.size() ; i++){
                                    table[i]->moveRight();
                                }
                            }

                            _Player1->refreshDepth();
                            cdc->refreshDepth(); cdc->refreshCardsPosition();

                            return true;
                            // .......................................
                            // END PROVERE ZA UBACIVANJE KARTE U GRUPU
                            // .......................................
                        }
                        else
                        {
                            _Player1->mouseReleaseEvent(m_event);
                            _Player1->refreshDepth();
                            qDebug() << "Karta ne odgovara za grupu!";
                        }
                    }
                }// END IF event->type() == QEvent::MouseButtonRelease
            }

            if( talon->isInArea()) {
                if(event->type() == QEvent::MouseButtonRelease && !firstTime) {
                    if(!playerOneOnMove) {
                        ui->errorLogger->setText("SACCEKAJ SVOJ RED");
                        _Player1->mouseReleaseEvent(m_event);
                    }
                    else if(!playerTookCard) {
                        ui->errorLogger->setText("PRVO UZMITE KARTU");
                        _Player1->mouseReleaseEvent(m_event);
                    }
                    else if( groupValue > 0 && groupValue <52 && !_Player1->alreadyOpened) {
                        ui->errorLogger->setText("otvaranje mora da ima vrednost preko 52");
                        _Player1->mouseReleaseEvent(m_event);
                    }
                    else if(playerTookCardFromTalon && groupValue == 0 && !_Player1->alreadyOpened) {
                        ui->errorLogger->setText("uzeli ste kartu sa talona, morate da se otvorite");
                        _Player1->mouseReleaseEvent(m_event);
                    }/*
                    else if(!firstTime && playerTookCardFromTalon) {
                        firstTime = false;
                    }*/
                    else {
                        //DEO ZA MREZU!!!!
                        emit onCardThrown(_Player1->getTempCard()->name());
                        playerToTalon();
                        talon->mouseReleaseEvent(m_event);

                        emit _Player1->onThrowCard();
//                        groupValue = 0;

                        ui->undoGroup->hide();
                        ui->undoTookTalonCard->hide();

                        playerTookCardFromTalon = false;

                        /*
                        if(!endGameFlag)
                            playerTwoPlay(); */

                        talon->mouseReleaseEvent(m_event);
                    }

                } // END IF event->type() == MouseButtonRelease

                firstTime = false; // ne znam bas dal ovo ide ovde
            } // END IF talon->isInArea()


        }// END IF _Player1->isCardTargeted(target)

        // blokiramo diranje karata sa table
        bool isTableCardTarget = std::count_if(table.begin(), table.end(),
                                       [target](CardTableContainer* cdc){return cdc->isCardTargeted(target); });
        if( isTableCardTarget ) {
            event->ignore();
            return true;
        }


        if(deck->isCardTargeted(target)) {
            if(event->type() == QMouseEvent::MouseButtonPress) {
                if(playerTookCard)
                    ui->errorLogger->setText("KARTA VEC UZETA");
                else if(!playerOneOnMove)
                    ui->errorLogger->setText("SACEKAJ SVOJ RED");
                else {
                    emit onDeckCardTaken();
                    _Player1->addCard(deck->getLastCard(),true);
                    playerTookCard = true;
                    ui->errorLogger->setText("error logger.");
                }
            }
            return true;
        }

        if(talon->isCardTargeted(target)) {
            if(event->type() == QMouseEvent::MouseButtonPress) {
                if(playerTookCardFromTalon || playerTookCard)
                    ui->errorLogger->setText("KARTA VEC UZETA");
                else if(!playerOneOnMove)
                    ui->errorLogger->setText("SACEKAJ SVOJ RED");
                else {
                   playerTookCardFromTalon  = true;
                   playerTookCard           = true;
                   firstTime                = true;

                   ui->undoTookTalonCard->show();

                   cardFromTalon = talon->getLastCard();
                   //deal card
                   emit onTalonCardTaken();
                   _Player1->addCard(cardFromTalon, true);
                }
            }
            event->ignore();
            return true;
        }
     // END IF (MOUSE EVENT)
    }
    // ako nije mouse event pustimo ga da radi svoje
    return target->event(event);
}

// ....................................
// gui elementi i ostale nebitne metode
// ....................................


void Game::cardsPreordered(QVector<QString> cardNames)
{
    delete _Player1; delete deck;

    _Player1 = new PlayerContainer(this, 300, 450, 350, 100);
    deck = new Deck(this, 10, 250, 70, 100, cardNames); // init i shuffle
/*
    _Player1->installEventFilter(this);
    deck->installEventFilter(this);
*/
    // inicijalizacija signal-slotova
    initSnS();

    // podela karata
    for(int i=0; i<15; i++)
        _Player1->addCard(deck->getLastCard(), true);
}

void Game::slotReboot()
{
    qDebug() << "Performing application reboot...";
    qApp->exit( Game::EXIT_CODE_REBOOT );
}

void Game::on_actionSelect_theme_triggered()
{
    selectTheme = new SelectTheme(this);
    selectTheme->show();
}

void Game::showOnThrowButton(bool showUndoGroup)
{
    ui->throwGroup->show();
    if( showUndoGroup ) ui->undoGroup->show();
}
void Game::hideOnThrowButton(bool hideUndoGroup)
{
    ui->throwGroup->hide();
    if( hideUndoGroup ) ui->undoGroup->hide();
}

Game::~Game() { delete ui; }

void Game::on_actionChoose_cards_triggered() {   chooseCards->show();    }

Card* Game::createCardByString(const QString& string1)
{

    int number;
    Card::Sign sign;
    Card* c;

    QString string(string1.trimmed());

    if(string.length()==2)
    {
        if(string.at(0) == 'A')
            number=1;
        else if(string.at(0) == 'K')
            number=14;
        else if(string.at(0) == 'Q')
            number=13;
        else if(string.at(0) == 'J')
            number=12;
        else
            number = string.at(0).digitValue();

        if(string.at(1) == 'P')
            sign=Card::PIK;
        else if(string.at(1) == 'K')
            sign=Card::KARO;
        else if(string.at(1) == 'T')
            sign=Card::TREF;
        else
            sign=Card::HERC;

            c = new Card(this,number,number,sign);
    }
    else if(string.at(0) == 'J')
    {
        c = new Card(this,0,0,Card::JOKER);
    }
    else{
        if(string.at(2) == 'P')
            sign=Card::PIK;
        else if(string.at(2) == 'K')
            sign=Card::KARO;
        else if(string.at(2) == 'T')
            sign=Card::TREF;
        else
            sign=Card::HERC;

        c = new Card(this,10,10,sign);
    }

    return c;
}

void Game::on_lineEdit_returnPressed()
{
    ui->textEdit->append(ui->lineEdit->text());
    emit onNewMessage(ui->lineEdit->text());
    ui->lineEdit->setText("");
}

void Game::on_undoTookTalonCard_clicked()
{
    _Player1->removeCard(cardFromTalon);
    talon->addCard(cardFromTalon, true);
    playerTookCard = false;
    playerTookCardFromTalon = false;
    ui->undoTookTalonCard->hide();
}
