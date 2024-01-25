#ifndef COSTURERACUERPOS_H
#define COSTURERACUERPOS_H

#include <QThread>
#include <QSemaphore>
#include <QMutex>
#include <QTcpSocket>

class CostureraCuerpos : public QThread {
    Q_OBJECT
public:
    static int getNumMaxCuerpos();

    CostureraCuerpos(QSemaphore *cestaCuerpos, QMutex *mutexCuerpos, QSemaphore *cestaMangas, QTcpSocket *socket);

signals:
    void cuerpoProducedSignal();

protected:
    void run() override;

private:
    QSemaphore *cestaCuerpos;
    QMutex *mutexCuerpos;
    QSemaphore *cestaMangas;
    QTcpSocket *socket;

    void sendMessageToServer(const QString &message);
};

#endif // COSTURERACUERPOS_H
