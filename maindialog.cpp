#include "maindialog.h"
#include "ui_maindialog.h"
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QClipboard>
#include "authenticator.h"

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);

    createActions();
    connect(ui->saveSecretButton, SIGNAL(clicked(bool)), this, SLOT(saveSecretButtonClicked(bool)));
    connect(ui->copyToClipboardButton, SIGNAL(clicked(bool)), this, SLOT(copyToClipboardButtonClicked(bool)));

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    QPixmap image(100, 100);
    QPainter painter(&image);
    QFont font = painter.font();
    font.setPointSize(60);
    painter.setFont(font);
    painter.fillRect(image.rect(), Qt::yellow);
    painter.drawText(image.rect(), Qt::AlignCenter | Qt::AlignVCenter, "G");

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(QIcon(image));
    trayIcon->setToolTip(" ya ya");
    trayIcon->show();



//    connect(trayIcon, &QSystemTrayIcon::messageClicked, this, &MainDialog::messageClicked);
    connect(trayIcon, &QSystemTrayIcon::activated, this, &MainDialog::iconActivated);
}

void MainDialog::createActions()
{
    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, &QAction::triggered, this, &QWidget::hide);

    maximizeAction = new QAction(tr("Ma&ximize"), this);
    connect(maximizeAction, &QAction::triggered, this, &QWidget::showMaximized);

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, &QAction::triggered, this, &QWidget::showNormal);

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
}

void MainDialog::respondSecondsChanged(int seconds, QString pin)
{
    QPixmap image(100, 100);
    QPainter painter(&image);
    QFont font = painter.font();
    font.setPointSize(60);
    painter.setFont(font);
    painter.fillRect(image.rect(), Qt::yellow);
    painter.drawText(image.rect(), Qt::AlignCenter | Qt::AlignVCenter, QString::number(seconds));

    trayIcon->setIcon(QIcon(image));

    ui->copyToClipboardButton->setText(pin + " (Click to copy)");
}

void MainDialog::saveSecretButtonClicked(bool b)
{
    QString secret = ui->secretEditBox->text().simplified().replace(" ", "");
    if(authenticators.size() == 0)
    {
        Authenticator* a = new Authenticator(secret);
        connect(a, &Authenticator::secondsChanged, this, &MainDialog::respondSecondsChanged);
        authenticators.push_back(a);
    } else {
        authenticators.front()->setSecret(secret);
    }
}

void MainDialog::copyToClipboardButtonClicked(bool b)
{
    QClipboard *clipboard = QApplication::clipboard();
    Authenticator *a = authenticators.front();
    clipboard->setText(a->pin);
}

void MainDialog::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
//        iconComboBox->setCurrentIndex((iconComboBox->currentIndex() + 1) % iconComboBox->count());
        break;
    case QSystemTrayIcon::MiddleClick:
//        showMessage();
        break;
    default:
        ;
    }
}

//void MainDialog::showMessage()
//{
//    showIconCheckBox->setChecked(true);
//    QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(
//            typeComboBox->itemData(typeComboBox->currentIndex()).toInt());
//    trayIcon->showMessage(titleEdit->text(), bodyEdit->toPlainText(), icon,
//                          durationSpinBox->value() * 1000);
//}

//void MainDialog::messageClicked()
//{
//    QMessageBox::information(0, tr("Systray"),
//                             tr("Sorry, I already gave what help I could.\n"
//                                "Maybe you should try asking a human?"));
//}

MainDialog::~MainDialog()
{
    delete ui;
}
