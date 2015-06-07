#include "server.h"
#include <QtNetwork>
#include <QString>

Server::Server(QObject *parent)
    :QObject(parent)
{
    server = new QTcpServer(this);

    connect(server,SIGNAL(newConnection()),this, SLOT(newConnection()));

    if(!server->listen())
    {
        qDebug() << "Could not start server!";
    }
    else
    {
        qDebug() << "Listening...";
    }

    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

    qDebug() << "Server is running on :" << ipAddress << " port:" << server->serverPort();

}

void Server::newConnection()
{
    qDebug() << "Connecting...";

    socket = server->nextPendingConnection();

    connect(socket,SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket,SIGNAL(disconnected()), this, SLOT(disconnected()));

    qDebug() << "Connected!";

}

void Server::readyRead()
{

    QByteArray Data = socket->readAll();

    qDebug() << " Data in:" << Data;

    QString s(Data);
    resolveReadyRead(s);

    qDebug() << "Poslat signal...";

}

void Server::resolveReadyRead(const QString &message)
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
        emit cardTaken();
        break;
    default:
        qDebug() << "Nepoznat podatak!";
    }
}

void Server::disconnected()
{

    qDebug() << " Disconnected!";

    socket->deleteLater();

    //exit(0);


}

void Server::sendMessage(const QString &message)
{
    if (message.isEmpty())
            return;

    QString data = "MESSAGE " + message;
    qDebug() << "Slanje poruke " + data;
    socket->write(data.toUtf8());
}

void Server::sendCard(const QString &card)
{
    if (card.isEmpty())
            return;

    QString data = "CARD " + card;
    qDebug() << "Slanje karte " + data;
    socket->write(data.toUtf8());
}

void Server::sendGroupOfCards(const QString &cards)
{
    if (cards.isEmpty())
            return;

    QString data = "GROUP " + cards;
    qDebug() << "Slanje grupe " + data;
    socket->write(data.toUtf8());
}

void Server::sendGroupIndexes(const QString &number)
{
    if (number.isEmpty())
            return;

    QString data = "INDEXES " + number;
    qDebug() << "Slanje indeksa " + data;
    socket->write(data.toUtf8());
}

void Server::sendDeckSignal()
{
    qDebug() << "Slanje signala za deck!";
    QString data = "DECK";
    socket->write(data.toUtf8());
}
