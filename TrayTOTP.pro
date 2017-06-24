#-------------------------------------------------
#
# Project created by QtCreator 2017-05-06T09:25:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TrayTOTP
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    maindialog.cpp \
    authenticator.cpp \
    qgoogleauth/base32.cpp \
    qgoogleauth/hmac.cpp \
    qgoogleauth/qgoogleauth.cpp \
    libcppotp/bytes.cpp \
    libcppotp/otp.cpp \
    libcppotp/sha1.cpp

HEADERS  += maindialog.h \
    authenticator.h \
    qgoogleauth/base32.h \
    qgoogleauth/hmac.h \
    qgoogleauth/qgoogleauth.h \
    libcppotp/bytes.h \
    libcppotp/otp.h \
    libcppotp/sha1.h

FORMS    += maindialog.ui

DISTFILES += \
    qgoogleauth/OTPGenerator.m