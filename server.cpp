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


    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    //koristimo prvu adresu koja nije local-host
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    //u slucaju da nije pronasao nijednu,koristimo local-host
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

    qDebug() << "Server is running on :" << ipAddress << " port:" << server->serverPort();

    port = server->serverPort();

}

void Server::newConnection()
{
    qDebug() << "Connecting...";

    socket = server->nextPendingConnection();

    connect(socket,SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket,SIGNAL(disconnected()), this, SLOT(disconnected()));

    emit newClient();

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
    else if(list.at(0) == "TALON")
        currentDataType = Talon;
    else if(list.at(0) == "GROUPINDEX")
        currentDataType = GroupIndex;
    else if(list.at(0)== "TCARDRET")
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

void Server::disconnected()
{

    qDebug() << " Disconnected!";

    emit clientLeftTheGame();

    socket->deleteLater();

    //exit(0);

}

void Server::sendSignal(const QString &data)
{
    socket->write(data.toUtf8());
}

QString Server::getIp()
{
    return ipAddress;
}

int Server::getPort()
{
    return port;
}

