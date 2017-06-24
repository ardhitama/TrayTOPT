#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QSystemTrayIcon>
#include <QDialog>
#include <QMenu>
#include "authenticator.h"
#include <vector>
#include "qgoogleauth/qgoogleauth.h"

namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason);
    void respondSecondsChanged(int, QString);
    void saveSecretButtonClicked(bool);
    void copyToClipboardButtonClicked(bool);

private:
    void setIcon(int index, int number);
    void createActions();

    Ui::MainDialog *ui;

    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;
    QAction *saveSecretAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    std::vector<Authenticator*> authenticators;
};

#endif // MAINDIALOG_H
