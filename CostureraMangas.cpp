#include "costureramangas.h"

int CostureraMangas::getNumMaxMangas() {
    return 5; // Replace with your implementation
}

CostureraMangas::CostureraMangas(QSemaphore *cestaMangas, QSemaphore *cestaCuerpos, QMutex *mutexMangas, QMutex *mutexCuerpos, QTcpSocket *socket)
    : cestaMangas(cestaMangas), cestaCuerpos(cestaCuerpos), mutexMangas(mutexMangas), mutexCuerpos(mutexCuerpos), socket(socket) {}

void CostureraMangas::run() {
    while (true) {
        QThread::msleep(1000);

        mutexMangas->lock();
        if (cestaMangas->available() < getNumMaxMangas()) {
            cestaMangas->release();
            qDebug() << "Costurera de Mangas cosiendo una manga.    Mangas en el buffer:" << cestaMangas->available()
                     << "Cuerpos en el buffer:" << cestaCuerpos->available();

            emit mangaProducedSignal();
        }
        mutexMangas->unlock();
    }
}

void CostureraMangas::sendMessageToServer(const QString &message) {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);
    out << message;

    socket->write(block);
    socket->waitForBytesWritten();
}
