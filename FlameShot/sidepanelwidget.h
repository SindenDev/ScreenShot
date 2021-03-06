

#pragma once

#include <QWidget>
#include "color_wheel.hpp"

class QVBoxLayout;
class QPushButton;
class QLabel;
class QColorPickingEventFilter;
class QSlider;

class SidePanelWidget : public QWidget {
    Q_OBJECT

    friend class QColorPickingEventFilter;
public:
    explicit SidePanelWidget(QPixmap *p, QWidget *parent = nullptr);

signals:
    void colorChanged(const QColor &c);
    void thicknessChanged(const int &t);
    void togglePanel();

public slots:
    void updateColor(const QColor &c);
    void updateThickness(const int &t);

private slots:
    void updateColorNoWheel(const QColor &c);
    void updateCurrentThickness();

private slots:
    void colorGrabberActivated();
    void releaseColorGrab();

private:
    QColor grabPixmapColor(const QPoint &p);

    bool handleKeyPress(QKeyEvent *e);
    bool handleMouseButtonPressed(QMouseEvent *e);
    bool handleMouseMove(QMouseEvent *e);

    void updateGrabButton(const bool activated);

    QVBoxLayout *m_layout;
    QPushButton *m_colorGrabButton;
    color_widgets::ColorWheel *m_colorWheel;
    QLabel *m_colorLabel;
    QPixmap *m_pixmap;
    QColor m_colorBackup;
    QColor m_color;
    QSlider *m_thicknessSlider;
    int m_thickness;
    QColorPickingEventFilter *m_eventFilter;

};
