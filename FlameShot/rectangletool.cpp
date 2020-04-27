

#include "rectangletool.h"
#include <QPainter>

namespace {
#define PADDING_VALUE 2
}

RectangleTool::RectangleTool(QObject *parent) : AbstractTwoPointTool(parent) {
    m_supportsDiagonalAdj = true;
}

QIcon RectangleTool::icon(const QColor &background, bool inEditor) const {
    Q_UNUSED(inEditor);
    return QIcon(iconPath(background) + "square.svg");
}
QString RectangleTool::name() const {
    return QStringLiteral("矩形");
}

QString RectangleTool::nameID() {
    return QLatin1String("");
}

QString RectangleTool::description() const {
    return QStringLiteral("矩形工具");
}

CaptureTool* RectangleTool::copy(QObject *parent) {
    return new RectangleTool(parent);
}

void RectangleTool::process(QPainter &painter, const QPixmap &pixmap, bool recordUndo) {
    if (recordUndo) {
        updateBackup(pixmap);
    }
    painter.setPen(QPen(m_color, m_thickness));
    painter.setBrush(QBrush(m_color));
    painter.drawRect(QRect(m_points.first, m_points.second));
}

void RectangleTool::paintMousePreview(QPainter &painter, const CaptureContext &context) {
    painter.setPen(QPen(context.color, PADDING_VALUE + context.thickness));
    painter.drawLine(context.mousePos, context.mousePos);
}

void RectangleTool::drawStart(const CaptureContext &context) {
    m_color = context.color;
    m_thickness = context.thickness + PADDING_VALUE;
    m_points.first = context.mousePos;
    m_points.second = context.mousePos;
}

void RectangleTool::pressed(const CaptureContext &context) {
    Q_UNUSED(context);
}
