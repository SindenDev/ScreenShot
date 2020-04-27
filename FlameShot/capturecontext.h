
#pragma once

#include <QRect>
#include <QPoint>
#include <QPixmap>
#include <QPainter>

struct CaptureContext {
    // screenshot with modifications
    QPixmap screenshot;
    // unmodified screenshot
    QPixmap origScreenshot;
    // Selection area
    QRect selection;
    // Widget dimensions
    QRect widgetDimensions;
    // Selected tool color
    QColor color;
    // Path where the content has to be saved
    QString savePath;
    // Ofset of the capture widget based on the system's screen (top-left)
    QPoint widgetOffset;
    // Mouse position inside the widget
    QPoint mousePos;
    // Value of the desired thickness
    int thickness;
    // Mode of the capture widget
    bool fullscreen;

    QPixmap selectedScreenshotArea() const ;
};
