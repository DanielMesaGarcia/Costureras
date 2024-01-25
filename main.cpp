#include <QCoreApplication>
#include <QSemaphore>
#include <QMutex>
#include <QThread>
#include <QDebug>
#include <QtNetwork/QTcpSocket>
#include "server.h"
#include "costureramangas.h"
#include "costureracuerpos.h"
#include "ensamblador.h"

int maxMangas = CostureraMangas::getNumMaxMangas();
int maxCuerpos = CostureraCuerpos::getNumMaxCuerpos();


int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    Server server;

    QSemaphore cestaMangas(maxMangas);
    QSemaphore cestaCuerpos(maxCuerpos);
    QMutex mutexMangas;
    QMutex mutexCuerpos;

    QTcpSocket *socket = new QTcpSocket();
    socket->connectToHost("127.0.0.1", 40023);

    CostureraMangas costureraMangas(&cestaMangas, &cestaCuerpos, &mutexMangas, &mutexCuerpos, socket);
    CostureraCuerpos costureraCuerpos(&cestaCuerpos, &mutexCuerpos, &cestaMangas, socket);
    ensamblador ensamblador(&cestaMangas, &cestaCuerpos, &mutexMangas, &mutexCuerpos, socket);

    costureraMangas.start();
    costureraCuerpos.start();
    ensamblador.start();

    costureraMangas.wait();
    costureraCuerpos.wait();
    ensamblador.wait();

    return a.exec();
}
