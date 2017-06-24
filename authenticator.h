#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include <QTimer>
#include <QDateTime>
#include <memory>
#include <QDebug>
#include <QString>

class Authenticator : public QObject
{
    Q_OBJECT

public:
    Authenticator(QString);
    void setSecret(QString);
    ~Authenticator();
    QString pin;

signals:
    void secondsChanged(int, QString);

private slots:
    void respondQTimerElapsed();
    void waitTimeSynchronized();

private:
    QString key;
    qint64 currentMSecsSinceEpoch;
    QTimer* qTimerFactory(int, const char* /*slot*/);
    QTimer *qTimerSynchronizer = NULL;
    QTimer *qTimerElapsed = NULL;

    int secondsElapsed = 0;
    std::unique_ptr<QTimer> timer;
};

#endif // AUTHENTICATOR_H
