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
             Group,
             Indexes,
             Deck,
             Talon,
             GroupIndex,
             InitCards,
             TCardRet
         };
    Client(QObject *parent = 0, QString ip = "", int port = 0);
    ~Client();

    static int CONN_ERROR;

    void resolveReadyRead(const QString& message);

    void sendMessage(const QString& message);
    void sendCard(const QString& card);
    void sendGroupOfCards(const QString& cards);
    void sendGroupIndexes(const QString& number);
    void sendDeckSignal();
    void sendTalonSignal();
    void sendGroupCards(const QString& message);
    void sendTalonCardRetSignal(const QString& card);


private slots:
    void readyRead();
    void showError(QAbstractSocket::SocketError);

signals:
    void newMessage(const QString& message);
    void cardThrown(const QString& card);
    void groupThrown(const QString& cards);
    void groupsReturned(const QString& cards);
    void deckCardTaken();
    void talonCardTaken();
    void newGroupIndex(const QString& message);
    void initCards(const QString& cards);
    void talonCardRetSignal(const QString& card);

private:
    QTcpSocket *tcpSocket;
    quint16 blockSize;
    DataType currentDataType;

};


#endif // CLIENT_H
