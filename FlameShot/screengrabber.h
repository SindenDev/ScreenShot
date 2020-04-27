

#pragma once

#include "desktopinfo.h"
#include <QObject>

class ScreenGrabber : public QObject {
    Q_OBJECT
public:
    explicit ScreenGrabber(QObject *parent = nullptr);
    QPixmap grabEntireDesktop(bool &ok);
    QPixmap grabScreen(int screenNumber, bool &ok);

private:
    DesktopInfo m_info;
};
