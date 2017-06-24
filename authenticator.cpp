#include "authenticator.h"
#include "qgoogleauth/qgoogleauth.h"

Authenticator::Authenticator(QString key)
{
    qDebug() << "Authenticator Started";
    this->key = key;
    qTimerSynchronizer = qTimerFactory(1, SLOT(waitTimeSynchronized()));
    qTimerSynchronizer->start();
}

void Authenticator::waitTimeSynchronized()
{
    qint64 currentMSecsSinceEpoch = QDateTime::currentMSecsSinceEpoch();
    if(currentMSecsSinceEpoch % 1000 == 0)
    {
        this->currentMSecsSinceEpoch = currentMSecsSinceEpoch;
        qDebug() << "WaitTimeSynchronized: done";
        qTimerElapsed = qTimerFactory(60, SLOT(respondQTimerElapsed()));
        qTimerElapsed->start();
        qTimerSynchronizer->stop();
    }
}

void Authenticator::setSecret(QString secret)
{
    qDebug() << "New secret: " << secret;
    this->key = secret;
}

void Authenticator::respondQTimerElapsed()
{
    qint64 currentMSecsSinceEpoch = QDateTime::currentMSecsSinceEpoch();
    int delta = currentMSecsSinceEpoch - this->currentMSecsSinceEpoch;
    if(delta > 90 && !qTimerSynchronizer->isActive())
    {
        qDebug() << "RespondQTimerElapsed delta: " << delta;
        qTimerElapsed->stop();
        qTimerSynchronizer = qTimerFactory(1, SLOT(waitTimeSynchronized()));
        qTimerSynchronizer->start();
    }
    else
    {
        this->pin = QGoogleAuth::generatePin(this->key.toLocal8Bit());
        this->currentMSecsSinceEpoch = currentMSecsSinceEpoch;
        emit secondsChanged(30 - int(QDateTime::currentSecsSinceEpoch() % 30), pin);
    }
}

QTimer* Authenticator::qTimerFactory(int interval, const char* responder /*slot*/)
{
    QTimer *timer = new QTimer();
    timer->setInterval(interval);
    connect(timer, SIGNAL(timeout()), this, responder);
    return timer;
}

Authenticator::~Authenticator()
{
    delete qTimerElapsed;
    delete qTimerSynchronizer;
}
