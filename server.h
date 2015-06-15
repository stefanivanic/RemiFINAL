#ifndef SERVER_H
#define SERVER_H

#include <QTcpSocket>
#include <QTcpServer>

class Server : public QObject
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
            TCardRet
        };
   Server(QObject *parent = 0);
   QTcpSocket *socket;

   void resolveReadyRead(const QString& message);

   void sendMessage(const QString& message);
   void sendCard(const QString& card);
   void sendGroupOfCards(const QString& cards);
   void sendGroupIndexes(const QString& number);
   void sendDeckSignal();
   void sendTalonSignal();
   void sendGroupCards(const QString& message);
   void sendInitCards(const QString& cards);
   void sendTalonCardRetSignal(const QString& card);

signals:
   void newClient();
   void newMessage(const QString& message);
   void cardThrown(const QString& card);
   void groupThrown(const QString& cards);
   void groupsReturned(const QString& cards);
   void deckCardTaken();
   void talonCardTaken();
   void newGroupIndex(const QString& message);
   void talonCardRetSignal(const QString& card);

public slots:
    void newConnection();
    void readyRead();
    void disconnected();

private:
    QTcpServer *server;
    DataType currentDataType;

};



#endif // SERVER_H
