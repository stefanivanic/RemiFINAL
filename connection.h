#ifndef CONNECTION_H
#define CONNECTION_H

#include <QHostAddress>
#include <QString>
#include <QTcpSocket>
#include <QTime>
#include <QTimer>

#include <card.h>

static const int MaxBufferSize = 1024000;

class Connection : public QTcpSocket
{
    Q_OBJECT

public:
    enum ConnectionState {
        WaitingForGreeting,
        ReadingGreeting,
        ReadyForUse
    };
    enum DataType {
        PlainText,
        Ping,
        Pong,
        Greeting,
        Undefined,
        Card,
        Group
    };

    Connection(QObject *parent = 0);

    QString name() const;
    void setGreetingMessage(const QString &message);
    bool sendMessage(const QString &message);

    bool sendCard(const QString &card);
    bool sendGroupOfCards(const QString &cards);

signals:
    void readyForUse();
    void newMessage(const QString &from, const QString &message);
    void cardThrown(const QString &card);
    void groupThrown(const QString &cards);


protected:
    void timerEvent(QTimerEvent *timerEvent) Q_DECL_OVERRIDE;

private slots:
    void processReadyRead();
    void sendPing();
    void sendGreetingMessage();

private:
    int readDataIntoBuffer(int maxSize = MaxBufferSize);
    int dataLengthForCurrentDataType();
    bool readProtocolHeader();
    bool hasEnoughData();
    void processData();

    QString greetingMessage;
    QString username;
    QTimer pingTimer;
    QTime pongTime;
    QByteArray buffer;
    ConnectionState state;
    DataType currentDataType;
    int numBytesForCurrentDataType;
    int transferTimerId;
    bool isGreetingMessageSent;
};


#endif // CONNECTION_H
