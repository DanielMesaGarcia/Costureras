// ensamblador.cpp
#include "ensamblador.h"

ensamblador::ensamblador(QSemaphore *cestaMangas, QSemaphore *cestaCuerpos, QMutex *mutexMangas, QMutex *mutexCuerpos, QTcpSocket *socket)
    : cestaMangas(cestaMangas), cestaCuerpos(cestaCuerpos), mutexMangas(mutexMangas), mutexCuerpos(mutexCuerpos), socket(socket) {}

void ensamblador::run() {
    while (true) {
        QThread::msleep(3000);

        mutexMangas->lock();
        mutexCuerpos->lock();

        if (cestaMangas->available() >= 2 && cestaCuerpos->available() >= 1) {
            cestaMangas->acquire(2);
            cestaCuerpos->acquire();
            qDebug() << "Ensamblador ensamblando un jersey.         Mangas en el buffer:" << cestaMangas->available()
                     << "Cuerpos en el buffer:" << cestaCuerpos->available();

            sendMessageToServer("Jersey assembled");
        }

        mutexCuerpos->unlock();
        mutexMangas->unlock();
    }
}

void ensamblador::mangaProducedSlot() const {
    // Handle the manga produced signal
    qDebug() << "Slot: Received mangaProducedSignal";
    // Add any additional processing if needed
}

void ensamblador::cuerpoProducedSlot() const {
    // Handle the cuerpo produced signal
    qDebug() << "Slot: Received cuerpoProducedSignal";
    // Add any additional processing if needed
}

void ensamblador::sendMessageToServer(const QString &message) {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);
    out << message;

    socket->write(block);
    socket->waitForBytesWritten();
}
