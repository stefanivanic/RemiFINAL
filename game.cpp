#include "game.h"
#include "ui_game.h"

#include <QTime>
#include <QStringList>

Game::Game(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::Game),
    theme("default"), playerOneOnMove(true), playerTookCard(true),
    goodOpening(false), playerTookCardFromTalon(0),
    firstTime(true), groupsThrown(0), groupValue(0),
    endGameFlag(false)
{
    //server = new Server();
    client = new Client();

    ui->setupUi(this);
    this->setStyleSheet(QStringLiteral("border-image: url(./slike/default/dark_wood.jpg);"));

    ui->throwGroup->hide(); ui->undoGroup->hide();

    _Player1 = new PlayerContainer(this, 200, 350, 350, 100);

    // napravi kontejner za playera 2 ovo ne
    // moze ovako da ostane jer mora dinamicki da se menja
    // broj karata koje protivnik ima u ruci

    chooseCards = new ChooseCards(this);

    talon = new Talon(this, 0, 250, 100, 100);
    deck = new Deck(this, 50, 50, 100, 100); // init i shuffle

    _Player1->installEventFilter(this);

    talon->installEventFilter(this);
    deck->installEventFilter(this);

    // inicijalizacija signal-slotova
    initSnS();

    // podela karata
    for(int i=0; i<15; i++)
        _Player1->addCard(deck->getLastCard(), true);
    // u add card vise ne mora da se prosledjuje bool

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
    connect( _Player1, SIGNAL(onAddingCardtoGroup()),
                 this, SLOT(showOnThrowButton()));
    // nema grupe => nema dugmeta
    connect( _Player1, SIGNAL(onEmptyGroup()),
                 this, SLOT(hideOnThrowButton()));
    // za restart aplikacije
    connect( ui->menuBarRestartGame, SIGNAL(triggered()),
              this, SLOT(slotReboot()));

    connect( chooseCards, SIGNAL(cardsPreorderd(QVector<QString>)),
                    this, SLOT(cardsPreordered(QVector<QString>)));

    //PROBA ZA SERVER
   // connect(server,SIGNAL(newMessage(QString)),this,SLOT(appendMessage(QString)));
   // connect(ui->lineEdit, SIGNAL(on_lineEdit_returnPressed()), this, SLOT(sendMessage()));

    //PROBA ZA KLIJENTA
    connect(ui->lineEdit, SIGNAL(on_lineEdit_returnPressed()), this, SLOT(on_lineEdit_returnPressed()));
    connect(client,SIGNAL(newMessage(QString)), this, SLOT(appendMessage(QString)));

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

    groupsThrown = 0;
    groupValue = 0;

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
    }
    else {
        int retValue = _Player1->group->isCorrectGroup();
        if( retValue < 0) {
            switch( retValue ) {
            case -1 : ui->errorLogger->setText("-1 : manje od 3 karte!"); break;
            case -2 : ui->errorLogger->setText("-2 : vise djokera!"); break;
            case -3 : ui->errorLogger->setText("-3 : niti su istog znaka niti su svi razlicitog"); break;
            case -4 : ui->errorLogger->setText("-4 : razlicitog znaka ali i razlicite vr"); break;
            case -5 : ui->errorLogger->setText("-5 : istog znaka ali brojevi nisu dobri"); break;
            default : ui->errorLogger->setText("nepoznaa greska" + QString::number(retValue)); break;
            }
        }
        else {
            if(_Player1->group->getCards().size() == (int)_Player1->handSize()) {
                ui->errorLogger->setText("mora da vam ostane bar 1 karta");
            }
            else {
//                ui->errorLogger->setText("");
                groupValue += retValue;
                ui->groupValue->setText("group value :" + QString::number(groupValue));

                int w1 = _Player1->group->getCards().size() * 20;
                int pos_x = std::accumulate(table.begin() + table.size() / 3 * 3,
                                            table.end(),
                                            200,
                                            [](const int& a, CardTableContainer* cdc)
                                                { return a + cdc->getContainerWidth(); } );
                int pos_y = 150 + (table.size() / 3 ) * 100;

                CardTableContainer* cdc =
                        new CardTableContainer(this, pos_x, pos_y, w1, 100);

                // i dodajemo u grupu i brisemo iz playera

                cdc->addCards(_Player1->group->getCards());
                _Player1->deleteCardsFromGroup();

                groupsThrown++;

                table.push_back(cdc); 
            }
        }
    }

    if(groupValue > 51)
        _Player1->alreadyOpened = true;
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
//
                _Player1->resolveMouseEvent(m_event);
            }

            if(isInTable) {
                CardTableContainer* cdc = NULL;
                for(int i=0; i<table.size(); i++) {
                    if(table[i]->isInArea()) {
                        cdc = table[i]; break; }
                }
                if(event->type() == QEvent::MouseButtonRelease) {
                    if( cdc != nullptr) {

                        Group g;
                        for(int i=0; i<cdc->CardContainer::getCards().size(); i++)
                            g.addCard(cdc->CardContainer::getCards()[i]);
                        g.addCard(_Player1->getTempCard());

                        int value =g.isCorrectGroup(); //ovde mi izmeni vrednost jokera
                        qDebug() << value;

                        if(value > 0){

                            int jokerFlag = -1;
                            int firstValue, lastValue;
                            int tempCardValue = _Player1->getTempCard()->getValue();


                            firstValue = cdc->CardContainer::getCards()[0]->getValue();
                            lastValue = cdc->CardContainer::getCards().last()->getValue();

                        int i;
                        for(i=0; i<cdc->CardContainer::getCards().size(); i++)
                            if(cdc->CardContainer::getCards()[i]->getSign() == Card::JOKER)
                            {
                                jokerFlag = i;
                                qDebug() << "Jokerflag: " << jokerFlag << "vrednost: " << cdc->CardContainer::getCards()[jokerFlag]->getValue();
                                break;
                            }

                            for(i=0; i<cdc->CardContainer::getCards().size(); i++)
                                if(cdc->CardContainer::getCards()[i]->getSign() == Card::JOKER)
                                {
                                    jokerFlag = i;
                                    qDebug() << "Jokerflag: " << jokerFlag << "vrednost: " << cdc->CardContainer::getCards()[jokerFlag]->getValue();
                                    break;
                                }


                            //sve ovo samo za isti znak
                            if(jokerFlag != -1 && tempCardValue == cdc->CardContainer::getCards()[jokerFlag]->getValue())
                            {
                                //ako kartu koju dodajemo menjamo za jokera
                                _Player1->addCard(cdc->CardContainer::getCards()[jokerFlag], true);
                                cdc->CardContainer::getCards()[jokerFlag] = _Player1->getTempCard();
                                _Player1->refreshDepth();
                                cdc->refreshDepth();
                                qDebug() << "Karta zamenjena za jokera!";

                            }
                            else if(tempCardValue == (lastValue+1)
                                    || ( tempCardValue == (lastValue+2) && lastValue == 10))
                            {
                                //ako kartu dodajemo na kraj
                                cdc->addCard(_Player1->getTempCard(), true);
                                _Player1->removeCard();
                                _Player1->refreshDepth();
                                cdc->refreshDepth();
                                qDebug() << "Karta dodata na kraj!";
                                qDebug() << "Lastvalue: " << lastValue << "firstVAlue: " << firstValue;
                            }
                            else if((tempCardValue == firstValue-1 && firstValue != 1)
                                    || ( tempCardValue == firstValue-2 && firstValue == 12 ))
                            {
                                //ako kartu dodajemo na pocetak
                                cdc->addCard(_Player1->getTempCard(), true);
                                _Player1->removeCard();
                                _Player1->refreshDepth();                    

                                qDebug() << cdc->printCards();
                                cdc->refreshDepth();
                                cdc->refreshCardsPosition();
                                qDebug() << "Karta dodata na pocetak";
                                qDebug() << "Lastvalue: " << lastValue << "firstVAlue: " << firstValue;
                            }
                            else if(tempCardValue == 0)
                            {
                                //ako je karta JOKER
                                if(lastValue == 15)
                                    {}//dodaj na pocetak
                                else{}
                                    //dodaj na kraj

                            }
                            else if(lastValue < firstValue)
                            {
                                //ovo je slucaj kad je joker na kraju, a on ga prebaci na pocetak
                                qDebug() << "Ne znam sta sad!?";
                                qDebug() << "Lastvalue: " << lastValue << "firstVAlue: " << firstValue;
                            }
                        }
                        else
                        {
                            _Player1->mouseReleaseEvent(m_event);
                            _Player1->refreshDepth();
                            qDebug() << "Karta ne odgovara za grupu!";
                        }

                        return true;
                    }
                }
                else
                    _Player1->resolveMouseEvent(m_event);
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
                         playerToTalon();
                        talon->mouseReleaseEvent(m_event);

//                        a zasto ovde emit kad moze direkt
//                        da se pozove slot metoda? ubaciti
//                        u odgovarajucu funkciju.
                        emit _Player1->onThrowCard();
//                        groupValue = 0;

                        ui->undoGroup->hide();

                        playerTookCardFromTalon = false;

                        /* ovaj deo ne treba al mozda treba da se zameni sa necim
                        if(!endGameFlag)
                            playerTwoPlay();
                          */
                        talon->mouseReleaseEvent(m_event);
                    }

                } // END IF event->type() == MouseButtonRelease
                firstTime = false;
            } // END IF talon->isInArea()


        }// END IF _Player1->isCardTargeted(target)

        /* ne treba al neka stoiji
        // blokiraj diranje tudjih karata
        if( _Player2->isCardTargeted(target) ) {
            event->ignore();
            return true;
        }
           */
        if(deck->isCardTargeted(target)) {
            if(event->type() == QMouseEvent::MouseButtonPress) {
                if(playerTookCard)
                    ui->errorLogger->setText("KARTA VEC UZETA");
                else if(!playerOneOnMove)
                    ui->errorLogger->setText("SACEKAJ SVOJ RED");
                else {
                    _Player1->addCard(deck->getLastCard(), true);
                    playerTookCard = true;
                    ui->errorLogger->setText("error logger.");
                }
            }
            event->ignore();
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
                   //deal card
                   _Player1->addCard(talon->getLastCard(), true);
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

void Game::showOnThrowButton() { ui->throwGroup->show(); ui->undoGroup->show(); }
void Game::hideOnThrowButton() { ui->throwGroup->hide(); }

Game::~Game() { delete ui; }

void Game::on_actionChoose_cards_triggered()
{
    chooseCards->show();
}

void Game::appendMessage(const QString &message)
{
    ui->textEdit->append(message);
}

void Game::on_lineEdit_returnPressed()
{
    QString s(ui->lineEdit->text());
    client->sendMessage(s);
}

void Game::cardsPreordered(QVector<QString> cardsName)
{
    qDebug() << "doso do slota";


    delete _Player1;
    delete talon;

    _Player1 = new PlayerContainer(this, 200, 350, 350, 100);
    talon = new Talon(this, 0, 250, 100, 100);


    delete deck;
    deck = new Deck(this, 50, 50, 100, 100, cardsName); // init i shuffle

    _Player1->installEventFilter(this);

    talon->installEventFilter(this);
    deck->installEventFilter(this);

    initSnS();

    qDebug() << deck->printCards();

    for(int i=0; i<15; i++)
        _Player1->addCard(deck->getLastCard(), true);

    _Player->refreshDepth();
}

void Game::sendMessage()
{
    QString s(ui->lineEdit->text());
    //server->sendMessage(s);
}
