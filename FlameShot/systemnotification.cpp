#include "systemnotification.h"
#include "confighandler.h"
#include <QApplication>
#include <QUrl>
#include "controller.h"

SystemNotification::SystemNotification(QObject *parent) : QObject(parent) {
    m_interface = nullptr;
}

void SystemNotification::sendMessage(const QString &text, const QString &savePath) {
    sendMessage(text, QStringLiteral("Flameshot пео╒"), savePath);
}

void SystemNotification::sendMessage(
        const QString &text,
        const QString &title,
        const QString &savePath,
        const int timeout)
{
    if(!ConfigHandler().desktopNotificationValue()) {
        return;
    }
    auto c = Controller::getInstance();
    c->sendTrayNotification(text, title, timeout);
}
