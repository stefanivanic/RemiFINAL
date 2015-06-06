#include "client.h"

#include <QHostAddress>

Client::Client(QObject *parent)
    :QObject(parent)
{

    tcpSocket = new QTcpSocket(this);

    tcpSocket->abort();

    tcpSocket->connectToHost("192.168.0.16",50287);

    if(tcpSocket->waitForConnected(3000))
    {
       qDebug() << "Connected！";

    }
    else
    {
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
    default:
        qDebug() << "Nepoznat podatak!";
    }
}


void Client::showError(QAbstractSocket::SocketError)
{
   qDebug() <<  tcpSocket->errorString();
}

void Client::sendMessage(const QString &message)
{
    QByteArray data = message.toUtf8();

    tcpSocket->write(data);
}

void Client::sendCard(const QString &card)
{
    if (card.isEmpty())
            return;

    qDebug() << "Slanje karte " + card;

    tcpSocket->write(card.toUtf8());
}

void Client::sendGroupOfCards(const QString &cards)
{
    if (cards.isEmpty())
            return;

    QString data = "GROUP " + cards;
    qDebug() << "Slanje grupe " + cards;
    tcpSocket->write(data.toUtf8());
}


