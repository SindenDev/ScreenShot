

#include "controller.h"
#include "capturewidget.h"
#include "confighandler.h"
#include "capturebutton.h"
#include "systemnotification.h"
#include "screengrabber.h"
#include <QFile>
#include <QApplication>
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>
#include <QDesktopWidget>
#include "globalshortcutfilter.h"

Controller::Controller() : m_captureWindow(nullptr) {
    GlobalShortcutFilter *nativeFilter = new GlobalShortcutFilter(this);
    qApp->installNativeEventFilter(nativeFilter);
    connect(nativeFilter, &GlobalShortcutFilter::printPressed,
            this, [this](){
        this->requestCapture(CaptureRequest(CaptureRequest::GRAPHICAL_MODE));
    });
    QString StyleSheet = CaptureButton::globalStyleSheet();
    qApp->setStyleSheet(StyleSheet);
}

Controller *Controller::getInstance() {
    static Controller c;
    return &c;
}

void Controller::enableExports() {
    connect(this, &Controller::captureTaken,
            this, &Controller::handleCaptureTaken);
    connect(this, &Controller::captureFailed,
            this, &Controller::handleCaptureFailed);
}

void Controller::requestCapture(const CaptureRequest &request) {
    uint id = request.id();
    m_requestMap.insert(id, request);

    switch (request.captureMode()) {
    case CaptureRequest::FULLSCREEN_MODE:
        doLater(request.delay(), this, [this, id](){
            this->startFullscreenCapture(id);
        });
        break;
    case CaptureRequest::SCREEN_MODE: {
        int &&number = request.data().toInt();
        doLater(request.delay(), this, [this, id, number](){
            this->startScreenGrab(id, number);
        });
        break;
    } case CaptureRequest::GRAPHICAL_MODE: {
        QString &&path = request.path();
        doLater(request.delay(), this, [this, id, path](){
            this->startVisualCapture(id, path);
        });
        break;
    } default:
        emit captureFailed(id);
        break;
    }
}

// creation of a new capture in GUI mode
void Controller::startVisualCapture(const uint id, const QString &forcedSavePath) {
    if (!m_captureWindow) {
        QWidget *modalWidget = nullptr;
        do {
            modalWidget = qApp->activeModalWidget();
            if (modalWidget) {
                modalWidget->close();
                modalWidget->deleteLater();
            }
        } while (modalWidget);

        m_captureWindow = new CaptureWidget(id, forcedSavePath);
        //m_captureWindow = new CaptureWidget(id, forcedSavePath, false); // debug
        connect(m_captureWindow, &CaptureWidget::captureFailed,
                this, &Controller::captureFailed);
        connect(m_captureWindow, &CaptureWidget::captureTaken,
                this, &Controller::captureTaken);
        m_captureWindow->show();
    } else {
        emit captureFailed(id);
    }
}

void Controller::startScreenGrab(const uint id, const int screenNumber) {
    bool ok = true;
    int n = screenNumber;

    if (n < 0) {
        QPoint globalCursorPos = QCursor::pos();
        n = qApp->desktop()->screenNumber(globalCursorPos);
    }
    QPixmap p(ScreenGrabber().grabScreen(n, ok));
    if (ok) {
        emit captureTaken(id, p);
    } else {
        emit captureFailed(id);
    }
}

void Controller::sendTrayNotification(
        const QString &text,
        const QString &title,
        const int timeout)
{
    if (m_trayIcon) {
        m_trayIcon->showMessage(title, text, QSystemTrayIcon::Information, timeout);
    }
}

void Controller::takeScreenshot()
{
    doLater(400, this, [this](){ this->startVisualCapture(); });
}

void Controller::startFullscreenCapture(const uint id) {
    bool ok = true;
    QPixmap p(ScreenGrabber().grabEntireDesktop(ok));
    if (ok) {
        emit captureTaken(id, p);
    } else {
        emit captureFailed(id);
    }
}

void Controller::handleCaptureTaken(uint id, QPixmap p) {
    auto it = m_requestMap.find(id);
    if (it != m_requestMap.end()) {
        it.value().exportCapture(p);
        m_requestMap.erase(it);
    }
    if (ConfigHandler().closeAfterScreenshotValue()) {
        QApplication::quit();
    }
}

void Controller::handleCaptureFailed(uint id) {
    m_requestMap.remove(id);

    if (ConfigHandler().closeAfterScreenshotValue()) {
        QApplication::quit();
    }
}

void Controller::doLater(int msec, QObject *receiver, lambda func)  {
    QTimer *timer = new QTimer(receiver);
    QObject::connect(timer, &QTimer::timeout, receiver,
                     [timer, func](){ func(); timer->deleteLater(); });
    timer->setInterval(msec);
    timer->start();
}
