#include "client.h"

#include <QHostAddress>

int Client::CONN_ERROR = 0;

Client::Client(QObject *parent, QString ip, int port)
    :QObject(parent)
{

    tcpSocket = new QTcpSocket(this);

    tcpSocket->abort();

    tcpSocket->connectToHost(ip, port);

    if(tcpSocket->waitForConnected(3000))
    {
       qDebug() << "Connected！";
    }
    else
    {
        CONN_ERROR = 1;
        qDebug() << "Connection Error！";
    }


    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(showError(QAbstractSocket::SocketError)));

    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readyRead()));

}

Client::~Client()
{
    delete tcpSocket;
}

void Client::readyRead(){

    QByteArray data = tcpSocket->readAll();

    QString s(data);
    resolveReadyRead(s);
}

void Client::resolveReadyRead(const QString &message)
{
    QStringList list = message.split(' ');

    QString buffer("");

    for(int i=1; i<list.size(); i++)
    {
        buffer.append(list.at(i));
        buffer.append(" ");
    }

    if(list.at(0) == "MESSAGE")
        currentDataType = Message;
    else if(list.at(0) == "CARD")
        currentDataType = Card;
    else if(list.at(0) == "GROUP")
        currentDataType = Group;
    else if(list.at(0) == "INDEXES")
        currentDataType = Indexes;
    else if(list.at(0) == "DECK")
        currentDataType = Deck;
    else if(list.at(0) == "TALON")
        currentDataType = Talon;
    else if(list.at(0) == "GROUPINDEX")
        currentDataType = GroupIndex;
    else if(list.at(0) == "INITCARDS")
        currentDataType = InitCards;
    else if(list.at(0) == "TCARDRET")
        currentDataType = TCardRet;
    else if(list.at(0) == "GAMEENDED")
        currentDataType = GameEnded;
    else
        currentDataType = Undefined;

    switch(currentDataType)
    {
    case Message:
        emit newMessage(buffer);
        break;
    case Card:
        emit cardThrown(buffer);
        break;
    case Group:
        emit groupThrown(buffer);
        break;
    case Indexes:
        emit groupsReturned(buffer);
        break;
    case Deck:
        emit deckCardTaken();
        break;
    case Talon:
        emit talonCardTaken();
        break;
    case GroupIndex:
        emit newGroupIndex(buffer);
        break;
    case InitCards:
        emit initCards(buffer);
        break;
    case TCardRet:
        emit talonCardRetSignal(buffer);
        break;
    case GameEnded:
        emit gameEndedSignal();
        break;
    default:
        qDebug() << "Nepoznat podatak!";
    }
}


void Client::showError(QAbstractSocket::SocketError)
{
   qDebug() <<  tcpSocket->errorString();
}

void Client::sendSignal(const QString &data)
{
    tcpSocket->write(data.toUtf8());
}
