#ifndef CLIENT_H
#define CLIENT_H


#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT

public:
    Client(QObject *parent = 0);
    ~Client();

private slots:
    void newConnect();
    void showError(QAbstractSocket::SocketError);
    void readyRead();
    void on_pushButton_clicked();
    void on_sendButton_clicked();

private:
    QTcpSocket *tcpSocket;
    quint16 blockSize;

};


#endif // CLIENT_H
