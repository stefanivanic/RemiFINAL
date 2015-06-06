#ifndef CLIENT_H
#define CLIENT_H


#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT

public:
    Client(QObject *parent = 0);
    ~Client();

    void sendMessage(const QString& message);


private slots:
    void readyRead();
    void showError(QAbstractSocket::SocketError);

signals:
    void newMessage(const QString& message);

private:
    QTcpSocket *tcpSocket;
    quint16 blockSize;

};


#endif // CLIENT_H
