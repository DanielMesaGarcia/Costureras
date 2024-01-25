// ensamblador.h
#ifndef ENSAMBLADOR_H
#define ENSAMBLADOR_H

#include <QThread>
#include <QSemaphore>
#include <QMutex>
#include <QTcpSocket>
#include <QSocketNotifier>

class ensamblador : public QThread {
    Q_OBJECT
public:
    ensamblador(QSemaphore *cestaMangas, QSemaphore *cestaCuerpos, QMutex *mutexMangas, QMutex *mutexCuerpos, QTcpSocket *socket);

public slots:
    void mangaProducedSlot() const;
    void cuerpoProducedSlot() const;

protected:
    void run() override;

private:
    QSemaphore *cestaMangas;
    QSemaphore *cestaCuerpos;
    QMutex *mutexMangas;
    QMutex *mutexCuerpos;
    QTcpSocket *socket;
    QSocketNotifier *notifier;  // Agregado

    void sendMessageToServer(const QString &message);
};

#endif // ENSAMBLADOR_H
