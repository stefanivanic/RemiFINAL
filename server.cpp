#include "server.h"
#include <QtNetwork>

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
    emit newMessage(s);

    qDebug() << "Poslat signal...";

   // socket->write(Data);

}

void Server::disconnected()
{

    qDebug() << " Disconnected!";

    socket->deleteLater();
//    exit(0);
}

void Server::sendMessage(const QString &message)
{
    socket->write(message.toUtf8());
}

