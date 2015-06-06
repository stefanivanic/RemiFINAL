#ifndef SERVER_H
#define SERVER_H

#include <QTcpSocket>
#include <QTcpServer>

class Server : public QObject
{
    Q_OBJECT
public:
   Server(QObject *parent = 0);
   QTcpSocket *socket;

signals:
   void newMessage(QString& message);

public slots:
    void newConnection();
    void readyRead();
    void disconnected();

private:
    QTcpServer *server;

};



#endif // SERVER_H
