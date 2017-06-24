#include "maindialog.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Tray TOTP"),
                              QObject::tr("Can't create system tray application."));
        return 1;
    }
    QApplication::setQuitOnLastWindowClosed(false);

    MainDialog w;
    w.show();

    return a.exec();
}
