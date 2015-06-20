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
            TCardRet,
            GameEnded
        };
   Server(QObject *parent = 0);
   QTcpSocket *socket;

   void resolveReadyRead(const QString& message);
   void sendSignal(const QString& data);

   QString getIp();
   int getPort();

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
   void gameEndedSignal();

public slots:
    void newConnection();
    void readyRead();
    void disconnected();

private:
    QTcpServer *server;
    DataType currentDataType;
    QString ipAddress;
    int port;

};



#endif // SERVER_H
