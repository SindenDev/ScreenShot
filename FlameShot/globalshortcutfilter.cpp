

#include "globalshortcutfilter.h"
#include "controller.h"
#include <qt_windows.h>

GlobalShortcutFilter::GlobalShortcutFilter(QObject *parent) :
    QObject(parent)
{
    // Forced Print Screen
    if (RegisterHotKey(NULL, 1, 0, VK_SNAPSHOT)) {
        // ok
    }
}

bool GlobalShortcutFilter::nativeEventFilter(
        const QByteArray &eventType,
        void *message,
        long *result)
{
    Q_UNUSED(eventType);
    Q_UNUSED(result);

    MSG* msg = static_cast<MSG*>(message);
    if (msg->message == WM_HOTKEY) {
        Controller::getInstance()->requestCapture(
                    CaptureRequest(CaptureRequest::GRAPHICAL_MODE));
        return true;
    }
    return false;
}
