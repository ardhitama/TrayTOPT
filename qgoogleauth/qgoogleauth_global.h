#ifndef QGOOGLEAUTH_GLOBAL_H
#define QGOOGLEAUTH_GLOBAL_H

#include <QtCore/qglbal.h>

#if defined(QGOOGLEAUTH_LIBRARY)
#  define QGOOGLEAUTHSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QGOOGLEAUTHSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QGOOGLEAUTH_GLOBAL_H
