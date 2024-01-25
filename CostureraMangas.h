#ifndef COSTURERAMANGAS_H
#define COSTURERAMANGAS_H

#include <QThread>
#include <QSemaphore>
#include <QMutex>
#include <QTcpSocket>

class CostureraMangas : public QThread {
    Q_OBJECT
public:
    CostureraMangas(QSemaphore *cestaMangas, QSemaphore *cestaCuerpos, QMutex *mutexMangas, QMutex *mutexCuerpos, QTcpSocket *socket);

    static int getNumMaxMangas();

signals:
    void mangaProducedSignal();

protected:
    void run() override;

private:
    QSemaphore *cestaMangas;
    QSemaphore *cestaCuerpos;
    QMutex *mutexMangas;
    QMutex *mutexCuerpos;
    QTcpSocket *socket;

    void sendMessageToServer(const QString &message);
};

#endif
