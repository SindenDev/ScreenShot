

#include "screengrabber.h"
#include "filenamehandler.h"
#include "systemnotification.h"
#include <QPixmap>
#include <QScreen>
#include <QGuiApplication>
#include <QApplication>
#include <QDesktopWidget>

ScreenGrabber::ScreenGrabber(QObject *parent) : QObject(parent) {

}

QPixmap ScreenGrabber::grabEntireDesktop(bool &ok) {
    ok = true;
    QRect geometry;
    for (QScreen *const screen : QGuiApplication::screens()) {
        geometry = geometry.united(screen->geometry());
    }

    QPixmap p(QApplication::primaryScreen()->grabWindow(
                  QApplication::desktop()->winId(),
                  geometry.x(),
                  geometry.y(),
                  geometry.width(),
                  geometry.height())
              );
    auto screenNumber = QApplication::desktop()->screenNumber();
    QScreen *screen = QApplication::screens()[screenNumber];
    p.setDevicePixelRatio(screen->devicePixelRatio());
    return p;
}

QPixmap ScreenGrabber::grabScreen(int screenNumber, bool &ok) {
    QPixmap p;
    bool isVirtual = QApplication::desktop()->isVirtualDesktop();
    if (isVirtual || m_info.waylandDectected()) {
        p = grabEntireDesktop(ok);
        if (ok) {
            QPoint topLeft(0, 0);
            for (QScreen *const screen : QGuiApplication::screens()) {
                QPoint topLeftScreen = screen->geometry().topLeft();
                if (topLeft.x() > topLeftScreen.x() ||
                        topLeft.y() > topLeftScreen.y()) {
                    topLeft = topLeftScreen;
                }
            }
            QRect geometry = QApplication::desktop()->
                    screenGeometry(screenNumber);
            geometry.moveTo(geometry.topLeft() - topLeft);
            p = p.copy(geometry);
        }
    } else {
        p = QApplication::desktop()->screen(screenNumber)->grab();
        ok = true;
    }
    return p;
}
