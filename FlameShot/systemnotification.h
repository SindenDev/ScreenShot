

#pragma once

#include <QObject>

class QDBusInterface;

class SystemNotification : public QObject {
    Q_OBJECT
public:
    explicit SystemNotification(QObject *parent = nullptr);

    void sendMessage(const QString &text,
                     const QString &savePath = {});

    void sendMessage(const QString &text,
                     const QString &title,
                     const QString &savePath,
                     const int timeout = 5000);

private:
    QDBusInterface *m_interface;
};
