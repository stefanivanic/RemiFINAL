#include "game.h"
#include "ui_game.h"

#include <QTime>
#include <QStringList>
#include <QMediaPlayer>
#include <QPropertyAnimation>

Game::Game(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::Game),
    theme("default"), playerOneOnMove(true), playerTookCard(true),
    goodOpening(false), playerTookCardFromTalon(0),
    firstTime(true), groupsThrown(0), groupValue(0),
    endGameFlag(false), playerTwoCardNumber(0)
{
    ui->setupUi(this);

    ui->throwGroup->hide(); ui->undoGroup->hide(); ui->undoTookTalonCard->hide();

    _Player1 = new PlayerContainer(this, 340, 490, 350, 100);

    chooseCards = new ChooseCards(this);

    deck = new Deck(this, 30, 250, 70, 100); // init i shuffle
    talon = new Talon(this, 120, 250, 70, 100);

    _Player1->installEventFilter(this);

    talon->installEventFilter(this);
    deck->installEventFilter(this);

    // inicijalizacija signal-slotova
    initSnS();

    // podela karata
    for(int i=0; i<15; i++)
        _Player1->addCard(deck->getLastCard(), true);
    // u add card vise ne mora da se prosledjuje bool


    song = new QMediaPlayer();
    song->setMedia(QUrl("qrc:/music/Calle_Real-Ya_lo_se.mp3"));
    song->setVolume(30);
    song->play();


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

    Card* c = createCardByString(_Player1->getTempCard()->name());
    _Player1->removeCard();

    // player je pobedio
    if(_Player1->handSize() == 0) {

        talon->addCard(c, false);
        emit onCardThrown(c->name()+" GAMEENDED");
     /*   endGameDialog = QMessageBox::question(this, "Restart",
                                        " Pobeda! Nova igra?",
                                        QMessageBox::Yes|QMessageBox::No);

        if (endGameDialog == QMessageBox::Yes)  emit slotReboot();
        else QApplication::quit();
     */
        endGameDialog = QMessageBox::information(this,"THE END!","You win!",QMessageBox::Ok);

        if(endGameDialog == QMessageBox::Ok)
        {
            QApplication::quit();
        }

        endGameFlag = true;
    }
    else{
        talon->addCard(c,true);
        emit onCardThrown(c->name());
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

/*void Game::changeTempPosText()
{
    QString s("Player1 : tempCardPosition : ");
    s.append( QString::number(_Player1->getTempCardPos()) );
    ui->label->setText(s);
}*/

// postavljaju se flegovi i ispisuju se loggeri
void Game::changePlayer()
{
    // .........................
    // privremeno, za debug !!!!
    // .........................
    playerOneOnMove = !playerOneOnMove;

    groupsThrown = 0;
    groupValue   = 0;

 /*   ui->errorLogger->setText("");
    ui->groupValue->setText("Vrednost grupe: 0");
*/
    QString s;
    if(playerOneOnMove)
        s="You are on move";
    else
        s="Opponent is on move";

    ui->onMoveLabel->setText(s);
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
        animation("First take card");
        return;
    }
    int retValue = _Player1->group->isCorrectGroup(true);
    if( retValue < 0) {
        switch( retValue ) {
        case -1 : animation("Less than 3 cards"); break;
        case -2 : animation("More than one joker"); break;
        case -3 : animation("Cars are not all same sign, nor different sign"); break;
        case -4 : animation("All cards are different signs and values"); break;
        case -5 : animation("Cards are same signs, but not appropriate values"); break;
        default : animation("Unknown error!"); break;
        //default : ui->errorLogger->setText("Nepoznata greška" + QString::number(retValue)); break;
        }
        return;
    }
    if(_Player1->group->getCards().size() == (int)_Player1->handSize()) {
        animation("You have to be left with at least 1 card");
        return;
    }
//      ui->errorLogger->setText("");
    groupValue += retValue;
    ui->groupValue->setText("Group value: " + QString::number(groupValue));

    int w1 = _Player1->group->getCards().size() * 20 + 60;
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
                        qDebug() << "provera koji je table: " << tableContainterPosition;
                        break;
                    }
                }
                if(event->type() == QEvent::MouseButtonRelease) {
                    if( cdc != nullptr) {
                        if(!_Player1->alreadyOpened){
                            _Player1->resolveMouseEvent(m_event);
                            _Player1->refreshCardsPosition();
                            _Player1->refreshDepth();
                            animation("You have to open firts");
                            return true;
                        }

                        if( _Player1->getCards().size() == 1) {
                            animation("You have to be left with at least 1 card");
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


                            bool imaDjokera = false;
                            for(int i=0; i < cdc->PlayerContainer::getCards().size(); i++) {
                                if(cdc->PlayerContainer::getCards()[i]->getSign() == Card::JOKER)
                                {
                                    imaDjokera = true;
                                    break;
                                }
                            }

                            if(imaDjokera) {
                                for(int i=0; i < g.getCards().size(); i++)
                                    if(g.getCards()[i]->getSign() == Card::JOKER)
                                    {
                                        jokerFlag = i;
                                        qDebug() << "Jokerflag: " << jokerFlag << "vrednost: " << g.getCards()[jokerFlag]->getValue();
                                        break;
                                    }
                            }

                            //qDebug() << "joker value : " << g.getCards()[jokerFlag]->getValue();

                            // .........................................
                            // BEGIN PROVERE ZA UBACIVANJE KARTE U GRUPU
                            // .........................................

                            _Player1->removeCard();
                            cdc->removeCards();

                            if(jokerFlag != -1) // postoji dzoker u grupi
                            {
                                if(_Player1->getTempCard()->getSign() != Card::JOKER)
                                {
                                    if(g.type() == Group::SAME_SIGN)
                                    {
                                        qDebug() << "radi se o grupi gde su istog znaka";

                                        if(g.getCards()[g.getCards().size()-1]->getSign() == Card::JOKER) {
                                            cdc->addCards(g.getCards().mid(0, g.getCards().size()-1));
                                            _Player1->addCard(g.getCards()[jokerFlag], true);
                                            resolveGroupChanged(&g,k,1);
                                        }
                                        else if(g.getCards()[0]->getSign() == Card::JOKER) {
                                             cdc->addCards(g.getCards().mid(1, g.getCards().size()));
                                             _Player1->addCard(g.getCards()[jokerFlag], true);
                                             resolveGroupChanged(&g,k,1);
                                        }
                                        else{
                                            cdc->addCards(g.getCards().mid(0, g.getCards().size()));
                                            resolveGroupChanged(&g,k,0);

                                            for(int i = tableContainterPosition + 1; i < granica && i < table.size() ; i++){
                                                table[i]->moveRight();
                                            }
                                        }

                                    }
                                    if(g.type() == Group::SAME_NUMBER)
                                    {
                                        qDebug() << "radi se o grupi gde su iste vrednosti";

                                        // VEC SU SVI ZNAKOVI ISTOG BROJA,
                                        // i dodajemo kartu i uzimamo dzokera
                                        if(g.getCards().size() == 5) {
                                            _Player1->addCard(g.getCards()[jokerFlag], true);
                                            cdc->addCards(g.getCards().mid(0, g.getCards().size()-1));

                                            resolveGroupChanged(&g,k,1);
                                        }

                                        // samo dodajemo kartu, i pomeramo sve ostale cdc udesno
                                        else
                                        {
                                            cdc->addCards(g.getCards().mid(0, g.getCards().size()));
                                            resolveGroupChanged(&g,k,0);

                                            int granica = (tableContainterPosition/3 + 1) * 3;
                                            qDebug() << "granica : " << granica;
                                            for(int i = tableContainterPosition + 1 ; i < granica && i < table.size() ; i++){
                                                table[i]->moveRight();
                                            }
                                        }
                                    }
                                }
                                else // djoker se baca u grupu
                                {
                                    cdc->addCards(g.getCards().mid(0, g.getCards().size()));
                                    resolveGroupChanged(&g,k,0);
                                }
                            }
                            else { // ne postoji djoker
                                qDebug() << "nema dzokera, samo dodajemo kartu u grupu na kraj";

                                cdc->addCards(g.getCards().mid(0, g.getCards().size()));

                                //DEO ZA MREZU!
                                resolveGroupChanged(&g,k,0);
                                //KRAJ DELA ZA MREZU!

                                int granica = (tableContainterPosition/3 +1) * 3;
//                                qDebug() << "granica : " << granica;
                                for(int i = tableContainterPosition + 1; i < granica && i < table.size() ; i++){
                                    table[i]->moveRight();
                                }
                            }

                            _Player1->refreshDepth(); _Player1->refreshCardsPosition();
                            cdc->refreshDepth(); cdc->refreshCardsPosition();

                                qDebug() << _Player1->printCards();
                                qDebug() << cdc->printCards();

                            return true;
                            // .......................................
                            // END PROVERE ZA UBACIVANJE KARTE U GRUPU
                            // .......................................
                        }
                        else
                        {
                            _Player1->mouseReleaseEvent(m_event);
                            _Player1->refreshDepth();
                            _Player1->refreshCardsPosition();
                            qDebug() << "Karta ne odgovara za grupu!";
                        }
                    }
                }// END IF event->type() == QEvent::MouseButtonRelease
            }

            if( talon->isInArea()) {
                if(event->type() == QEvent::MouseButtonRelease && !firstTime) {
                    if(!playerOneOnMove) {
                        animation("Wait your turn");
                        _Player1->mouseReleaseEvent(m_event);
                    }
                    else if(!playerTookCard) {
                        animation("First take card");
                        _Player1->mouseReleaseEvent(m_event);
                    }
                    else if( groupValue > 0 && groupValue <52 && !_Player1->alreadyOpened) {
                        animation("Total value of cards have to be grater than 51");
                        _Player1->mouseReleaseEvent(m_event);
                    }
                    else if(playerTookCardFromTalon && groupValue == 0 && !_Player1->alreadyOpened) {
                        animation("You have to open when take card from talon");
                        _Player1->mouseReleaseEvent(m_event);
                    }/*
                    else if(!firstTime && playerTookCardFromTalon) {
                        firstTime = false;
                    }*/
                    else {
                        changePlayer();
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

                firstTime = false; // ne znam bas da l ovo ide ovde
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
                    animation("Card already taken");
                else if(!playerOneOnMove)
                    animation("Wait your turn");
                else {
                    emit onDeckCardTaken();
                    _Player1->addCard(deck->getLastCard(),true);
                    playerTookCard = true;
                    animation("");
                }
            }
            return true;
        }

        if(talon->isCardTargeted(target)) {
            if(event->type() == QMouseEvent::MouseButtonPress) {
                if(playerTookCardFromTalon || playerTookCard)
                    animation("Card alredy taken");
                else if(!playerOneOnMove)
                    animation("Wait your turn");
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
    emit talonCardReturned(cardFromTalon->name());
}

void Game::playerTwoModCardNumber(int offset)
{
    playerTwoCardNumber += offset;

    for(QLabel* c : playerTwoCards)
        delete c;
    playerTwoCards.clear();

    for(int i=0; i<playerTwoCardNumber; i++) {
        playerTwoCards.push_back(new QLabel(this));

        QPixmap pix(QDir::currentPath()
                    + "/slike/Karte/" + "2_back" +
                    + ".jpg");
        playerTwoCards.back()->setPixmap(pix);

        playerTwoCards.back()->resize(pix.size().width(), pix.size().height());

        playerTwoCards.back()->move(310 + i*20, 40);
        playerTwoCards.back()->raise();
        playerTwoCards.back()->show();
    }
}
void Game::on_playStop_clicked()
{
    if(playing) {
        song->setVolume(0);
        playing=false;
        ui->playStop->setStyleSheet(QStringLiteral("border-image: url(./slike/Teme/notax.png);"));
    }
    else {
        song->setVolume(30);
        playing=true;
        ui->playStop->setStyleSheet(QStringLiteral("border-image: url(./slike/Teme/nota.png);"));
    }
}

void Game::resolveGroupChanged(Group *g,int k, int jokerFlag)
{
    //DEO ZA MREZU!
    QString message("");

    //iterator za grupu
    message.append(QString::number(k));

    if(jokerFlag==1)
        message.append("J");

    message.append(" ");

    for(int i=0; i<g->getCards().size(); i++){

          if(g->getCards()[i]->name()=="J")
          {
              if(jokerFlag==1)
                  continue;
          }

          message.append(g->getCards()[i]->name());
          message.append(" ");
    }

    emit onGroupCardAdd(message);
    qDebug() << "Poslat signal za dodavanje na grupu! " << message;
    //KRAJ DELA ZA MREZU!
}

void Game::animation(const QString& message)
{
     ui->errorLogger->setText(message);
     QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect(ui->errorLogger);
     opacityEffect->setOpacity(0);
     ui->errorLogger->setGraphicsEffect(opacityEffect);
     QPropertyAnimation* anim = new QPropertyAnimation(ui->errorLogger);
     anim->setTargetObject(opacityEffect);
     anim->setPropertyName("opacity");
     anim->setDuration(2500);
     anim->setStartValue(opacityEffect->opacity());
     anim->setEndValue(1.0);
     anim->setDuration(2500);
     anim->start(QAbstractAnimation::KeepWhenStopped);
}
