#ifndef CLIENT_H
#define CLIENT_H

#include <QAbstractSocket>
#include <QHash>
#include <QHostAddress>

#include "server.h"
#include "card.h"

class PeerManager;

class Client : public QObject
{
    Q_OBJECT

public:
    Client();

    void sendMessage(const QString &message);
    QString nickName() const;
    bool hasConnection(const QHostAddress &senderIp, int senderPort = -1) const;

    void sendCard(const QString& card);
    void sendGroupOfCards(const QString& cards);

signals:
    void newMessage(const QString &from, const QString &message);
    void newParticipant(const QString &nick);
    void participantLeft(const QString &nick);

    void cardThrown(const QString &card);
    void groupThrown(const QString &cards);


private slots:
    void newConnection(Connection *connection);
    void connectionError(QAbstractSocket::SocketError socketError);
    void disconnected();
    void readyForUse();

private:
    void removeConnection(Connection *connection);

    PeerManager *peerManager;
    Server server;
    QMultiHash<QHostAddress, Connection *> peers;
};

#endif
