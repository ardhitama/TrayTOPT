#ifndef QGOOGLEAUTH_H
#define QGOOGLEAUTH_H

#include <QString>

class QGoogleAuth {
public:
    static QString generatePin(const QByteArray key);
};

#endif // QGOOGLEAUTH_H
