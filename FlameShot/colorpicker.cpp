

#include "colorpicker.h"
#include "confighandler.h"
#include "globalvalues.h"
#include <QPainter>
#include <QMouseEvent>

ColorPicker::ColorPicker(QWidget *parent) : QWidget(parent) {
    ConfigHandler config;
    m_colorList = config.getUserColors();
    m_colorAreaSize = GlobalValues::buttonBaseSize() * 0.6;
    setMouseTracking(true);
    m_uiColor = config.uiMainColorValue();
    m_drawColor = config.drawColorValue();

    const int extraSize = 6;
    double radius = (m_colorList.size()*m_colorAreaSize/1.3)/(3.141592);
    resize(radius*2 + m_colorAreaSize + extraSize,
           radius*2 + m_colorAreaSize+ extraSize);
    double degree = 360 / (m_colorList.size());
    double degreeAcum = degree;

    QLineF baseLine = QLineF(QPoint(radius+extraSize/2, radius+extraSize/2),
                             QPoint(radius*2, radius));

    for (int i = 0; i<m_colorList.size(); ++i) {
        m_colorAreaList.append(QRect(baseLine.x2(), baseLine.y2(),
                                 m_colorAreaSize, m_colorAreaSize));
        baseLine.setAngle(degreeAcum);
        degreeAcum += degree;
    }
}

QColor ColorPicker::drawColor() {
    return m_drawColor;
}

void ColorPicker::show() {
    grabMouse();
    QWidget::show();
}

void ColorPicker::hide() {
    releaseMouse();
    QWidget::hide();
}

void ColorPicker::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QVector<QRect> rects = handleMask();
    painter.setPen(QColor(Qt::black));
    for (int i = 0; i < rects.size(); ++i) {
        // draw the highlight when we have to draw the selected color
        if (m_drawColor == QColor(m_colorList.at(i))) {
            QColor c = QColor(m_uiColor);
            c.setAlpha(155);
            painter.setBrush(c);
            c.setAlpha(100);
            painter.setPen(c);
            QRect highlight = rects.at(i);
            highlight.moveTo(highlight.x() - 3, highlight.y() - 3);
            highlight.setHeight(highlight.height() + 6);
            highlight.setWidth(highlight.width() + 6);
            painter.drawRoundRect(highlight, 100, 100);
            painter.setPen(QColor(Qt::black));
        }
        painter.setBrush(QColor(m_colorList.at(i)));
        painter.drawRoundRect(rects.at(i), 100, 100);
    }
}

void ColorPicker::mouseMoveEvent(QMouseEvent *e) {
    for (int i = 0; i < m_colorList.size(); ++i) {
        if (m_colorAreaList.at(i).contains(e->pos())) {
            m_drawColor = m_colorList.at(i);
            emit colorSelected(m_drawColor);
            update();
            break;
        }
    }
}

QVector<QRect> ColorPicker::handleMask() const {
    QVector<QRect> areas;
    for (const QRect &rect: m_colorAreaList) {
        areas.append(rect);
    }
    return areas;
}
