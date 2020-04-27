
#pragma once

#include "capturerequest.h"
#include <QObject>
#include <QPointer>
#include <QPixmap>
#include <QMap>
#include <QTimer>
#include <functional>
#include "flameshot_global.h"

class CaptureWidget;
class ConfigWindow;
class InfoWindow;
class QSystemTrayIcon;

using lambda = std::function<void(void)>;

class FLAMESHOTSHARED_EXPORT Controller : public QObject {
    Q_OBJECT

public:
    static Controller* getInstance();

    Controller(const Controller&) = delete;
    void operator =(const Controller&) = delete;

    void enableExports();

signals:
    void captureTaken(uint id, QPixmap p);
    void captureFailed(uint id);

public slots:
    void requestCapture(const CaptureRequest &request);
    void sendTrayNotification(const QString &text,
                              const QString &title = QStringLiteral("Flameshot Info"),
                              const int timeout = 5000);
    void takeScreenshot();

private slots:
    void startFullscreenCapture(const uint id = 0);
    void startVisualCapture(const uint id = 0,
                             const QString &forcedSavePath = QString());
    void startScreenGrab(const uint id = 0, const int screenNumber = -1);

    void handleCaptureTaken(uint id, QPixmap p);
    void handleCaptureFailed(uint id);

private:
    Controller();

    // replace QTimer::singleShot introduced in Qt 5.4
    // the actual target Qt version is 5.3
    void doLater(int msec, QObject *receiver, lambda func);

    QMap<uint, CaptureRequest> m_requestMap;
    QPointer<CaptureWidget> m_captureWindow;
    QPointer<QSystemTrayIcon> m_trayIcon;
};
