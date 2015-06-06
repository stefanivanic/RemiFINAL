#include "client.h"

#include <QHostAddress>

Client::Client(QObject *parent)
    :QObject(parent)
{

    tcpSocket = new QTcpSocket(this);

    tcpSocket->abort();

    tcpSocket->connectToHost("169.254.247.12",50537);

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
    emit newMessage(s);
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
