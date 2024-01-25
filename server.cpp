#include "server.h"

#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>

Server::Server(QObject *parent)
    : QObject{parent}
{
    server = new QTcpServer(this);

    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    if(!server->listen(QHostAddress::Any, 40023))
    {
        qDebug() << "Server could not start!";
    }
    else
    {
        qDebug() << "Server started!" << server->serverAddress() << ":" << server->serverPort();
    }
}

void Server::newConnection()
{
    qDebug() << "New Connection started from client";

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);

    out << QString("This is a message from server to client");

    QTcpSocket *clientConnection = server->nextPendingConnection();
    connect(clientConnection, &QAbstractSocket::disconnected,
            clientConnection, &QObject::deleteLater);

    clientConnection->write(block);

    qDebug() << "Message sent to client";

    clientConnection->disconnectFromHost();
}
