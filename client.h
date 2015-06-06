#ifndef CLIENT_H
#define CLIENT_H


#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT

public:
    enum DataType {
             Message,
             Undefined,
             Card,
             Group
         };
    Client(QObject *parent = 0);
    ~Client();

    void resolveReadyRead(const QString& message);

    void sendMessage(const QString& message);
    void sendCard(const QString& card);
    void sendGroupOfCards(const QString& cards);

private slots:
    void readyRead();
    void showError(QAbstractSocket::SocketError);

signals:
    void newMessage(const QString& message);
    void cardThrown(const QString& card);
    void groupThrown(const QString& cards);

private:
    QTcpSocket *tcpSocket;
    quint16 blockSize;
    DataType currentDataType;

};


#endif // CLIENT_H
