#include "costureracuerpos.h"

int CostureraCuerpos::getNumMaxCuerpos() {
    return 5; // Replace with your implementation
}

CostureraCuerpos::CostureraCuerpos(QSemaphore *cestaCuerpos, QMutex *mutexCuerpos, QSemaphore *cestaMangas, QTcpSocket *socket)
    : cestaCuerpos(cestaCuerpos), mutexCuerpos(mutexCuerpos), cestaMangas(cestaMangas), socket(socket) {}

void CostureraCuerpos::run() {
    while (true) {
        QThread::msleep(2000);

        mutexCuerpos->lock();
        if (cestaCuerpos->available() < getNumMaxCuerpos()) {
            cestaCuerpos->release();
            qDebug() << "Costurera de Cuerpos cosiendo un cuerpo.   Mangas en el buffer:" << cestaMangas->available()
                     << "Cuerpos en el buffer:" << cestaCuerpos->available();

            emit cuerpoProducedSignal();
        }
        mutexCuerpos->unlock();
    }
}

void CostureraCuerpos::sendMessageToServer(const QString &message) {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);
    out << message;

    socket->write(block);
    socket->waitForBytesWritten();
}
