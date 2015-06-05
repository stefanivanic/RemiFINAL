#include "game.h"
#include "ui_game.h"
#include "sign.h"


#include <QTime>
#include <QStringList>

bool playerOneOnMove;
bool playerTookCard;
bool goodOpening;
bool playerTookCardFromTalon;
bool firstTime;
int groupsThrown;
int groupValue;

Game::Game(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::Game),
    theme("default"), playerOneOnMove(true), playerTookCard(true),
    goodOpening(false), playerTookCardFromTalon(0),
    firstTime(true), groupsThrown(0), groupValue(0),
    endGameFlag(false)
{
    ui->setupUi(this);
    ui->throwGroup->hide(); ui->undoGroup->hide();

    _Player1 = new PlayerContainer(this, 200, 350, 350, 100);
    _Player2 = new PlayerContainer(this, 200,  50, 350, 100);

    talon = new Talon(this, 0, 250, 100, 100);
    deck = new Deck(this, 50, 50, 100, 100); // init i shuffle

    _Player1->installEventFilter(this);
    _Player2->installEventFilter(this);

    talon->installEventFilter(this);
    deck->installEventFilter(this);

    // inicijalizacija signal-slotova
    initSnS();

    dealCards();

    connect(ui->lineEdit, SIGNAL(on_lineEdit_returnPressed()),
            this, SLOT(on_lineEdit_returnPressed()));
    connect(ui->lineEdit, SIGNAL(on_lineEdit_returnPressed()),
            this, SLOT(on_lineEdit_returnPressed()));
    connect(&client, SIGNAL(newMessage(QString,QString)),
            this, SLOT(appendMessage(QString,QString)));
    connect(&client, SIGNAL(newParticipant(QString)),
            this, SLOT(newParticipant(QString)));
    connect(&client, SIGNAL(participantLeft(QString)),
            this, SLOT(participantLeft(QString)));

    //OVDE DODATO
    connect(&client, SIGNAL(cardThrown(QString)),
            this, SLOT(appendCard(QString)));

    connect(&client, SIGNAL(groupThrown(QString)),
            this, SLOT(appendGroupOfCards(QString)));

    myNickName = client.nickName();
    newParticipant(myNickName);

} // END CONSTRUCTOR

void Game::initSnS()
{
    // monitoring glega za tempCardPosition
    connect( _Player1, SIGNAL(onPositionChange()),
                 this, SLOT(changeTempPosText()));
    // bacili kartu => pomeraju se flegovi, tekst itd
    connect( _Player1, SIGNAL(onThrowCard()),
                 this, SLOT(changePlayer()));
    // bacili kartu => pomeraju se flegovi, tekst itd
    connect( _Player2, SIGNAL(onThrowCard()),
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
}

void Game::dealCards()
{
    dealCard(PLAYER1); for(int i=0; i<14; i++)
    {  dealCard(PLAYER1);  dealCard(PLAYER2);  }
}

void Game::dealCard(bool player2)
{
    PlayerContainer* player = player2 ? _Player2 : _Player1;
    player->addCard(deck->getLastCard(), !player2);
}

void Game::playerTwoPlay()
{
    _Player2->setTempCard();
    delay(1.5, "TAKING CARD");    dealCard(PLAYER2);
    delay(2.5, "THINKING"   );    playerToTalon(PLAYER2);

    // dal cemo ovde ili negde u playeru
    emit _Player2->onThrowCard();
}

void Game::playerToTalon(bool playerTwo)
{
    PlayerContainer* p = playerTwo ? _Player2 : _Player1;

    talon->addCard(p->getTempCard(), true);
    p->removeCard();

    // player je pobedio
    if(p->handSize() == 0) {
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
    PlayerContainer* p = playerOneOnMove ? _Player1 : _Player2 ;

    for( int i = 0 ; i < groupsThrown; i++){
        CardTableContainer* cdc = table.back();

        int size = cdc->handSize();
        for(int j = 0 ; j < size ; j++)
            p->addCard(cdc->getLastCard(), true);

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

void Game::delay(double seconds, QString message)
{
    ui->aiLogger->setText(message);

    QTime dieTime= QTime::currentTime().addSecs(seconds);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    ui->aiLogger->setText("CHILLING");
}

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


                //OVDE DODATO-------------------------------------------------
                onGroupOfCardsThrown();
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
                                if(cdc->CardContainer::getCards()[i]->getSign() == JOKER)
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
                        onCardThrown();
                        playerToTalon(PLAYER1);
                        talon->mouseReleaseEvent(m_event);

//                        a zasto ovde emit kad moze direkt
//                        da se pozove slot metoda? ubaciti
//                        u odgovarajucu funkciju.
                        emit _Player1->onThrowCard();
//                        groupValue = 0;

                        ui->undoGroup->hide();

                        playerTookCardFromTalon = false;

                        if(!endGameFlag)
                            playerTwoPlay();

                        talon->mouseReleaseEvent(m_event);
                    }

                } // END IF event->type() == MouseButtonRelease
                firstTime = false;
            } // END IF talon->isInArea()


        }// END IF _Player1->isCardTargeted(target)


        // blokiraj diranje tudjih karata
        if( _Player2->isCardTargeted(target) ) {
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
                    dealCard(PLAYER1);
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

//DODATO
void Game::appendMessage(const QString &from, const QString &message)
{
    if (from.isEmpty() || message.isEmpty())
        return;

    ui->textEdit->append(message);

}


void Game::newParticipant(const QString &nick)
{
    if (nick.isEmpty())
        return;

    ui->textEdit->append(nick +" has joined");

}

void Game::participantLeft(const QString &nick)
{
    if (nick.isEmpty())
        return;

    ui->textEdit->append(nick+" has left");

}

void Game::on_lineEdit_returnPressed()
{
    QString text = ui->lineEdit->text();
    if (text.isEmpty())
        return;


     client.sendMessage(text);
     appendMessage(myNickName, text);


    ui->lineEdit->clear();
}

void Game::onCardThrown()
{
    client.sendCard(_Player1->getTempCard()->name());
}

void Game::appendCard(const QString &card)
{
    //ovde
    Card* c = createCardByString(card);

    talon->addCard(c,true);

}

void Game::onGroupOfCardsThrown()
{
    QString cards = "";

    for(int i=0; i<_Player1->group->getCards().size(); i++)
        cards.append(_Player1->group->getCards()[i]->name()+" ");

    qDebug() << cards << " <--- Karte";

    client.sendGroupOfCards(cards);

}

void Game::appendGroupOfCards(const QString &cards)
{

    QStringList list = cards.split(' ');

    int w1 = list.size() * 20;
    int pos_x = std::accumulate(table.begin() + table.size() / 3 * 3,
                                table.end(),
                                200,
                                [](const int& a, CardTableContainer* cdc)
                                    { return a + cdc->getContainerWidth(); } );
    int pos_y = 150 + (table.size() / 3 ) * 100;

    CardTableContainer* cdc =
            new CardTableContainer(this, pos_x, pos_y, w1, 100);


    for(int i=0; i<list.size()-1; i++)
    {
        Card* c = createCardByString(list.at(i));
        cdc->addCard(c,true);
    }

    table.append(cdc);
}

Card* Game::createCardByString(const QString& string)
{

    int number;
    Sign sign;
    Card* c;

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
        sign=PIK;
    else if(string.at(1) == 'K')
        sign=KARO;
    else if(string.at(1) == 'T')
        sign=TREF;
    else
        sign=HERC;

        c = new Card(this,number,number,sign);
    }
    else if(string.at(0) == 'J')
    {
        c = new Card(this,0,0,JOKER);
    }
    else{
        if(string.at(2) == 'P')
            sign=PIK;
        else if(string.at(2) == 'K')
            sign=KARO;
        else if(string.at(2) == 'T')
            sign=TREF;
        else
            sign=HERC;

        c = new Card(this,10,10,sign);
    }

    return c;
}
