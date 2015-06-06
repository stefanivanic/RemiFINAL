#include "client.h"

Client::Client(QObject *parent)
    :QObject(parent)
{

    tcpSocket = new QTcpSocket(this);


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
   // messageBrowser->append(data);
}

void Client::newConnect()
{
    tcpSocket->abort();
   // tcpSocket->connectToHost("127.0.0.1",1234);

    if(tcpSocket->waitForConnected(3000))
    {
       qDebug() << "Connected！";

    }
    else
    {
        qDebug() << "Connection Error！";
    }

}

void Client::showError(QAbstractSocket::SocketError)
{
    // messageBrowser->append(QString("errorString：%1\n").arg(tcpSocket->errorString()));

}

void Client::on_pushButton_clicked()
{
    newConnect();
}

void Client::on_sendButton_clicked()
{
    QString message;

    if (message.isEmpty())
        return;

    QByteArray data = message.toUtf8();

    tcpSocket->write(data);

}


