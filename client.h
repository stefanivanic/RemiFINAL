#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT

public:
    enum DataType {
             Message,
             Card,
             Group,
             Indexes,
             Deck,
             Talon,
             GroupIndex,
             InitCards,
             TCardRet,
             GameEnded,
             Undefined
         };
    Client(QObject *parent = 0, QString ip = "", int port = 0);
    ~Client();

    static int CONN_ERROR;

    void resolveReadyRead(const QString& message);
    void sendSignal(const QString& data);


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
    void gameEndedSignal();

private:
    QTcpSocket *tcpSocket;
    quint16 blockSize;
    DataType currentDataType;

};


#endif // CLIENT_H
