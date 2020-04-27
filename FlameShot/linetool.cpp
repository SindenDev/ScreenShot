

#include "linetool.h"
#include <QPainter>

namespace {

#define PADDING_VALUE 2

}

LineTool::LineTool(QObject *parent) : AbstractTwoPointTool(parent) {
    m_supportsOrthogonalAdj = true;
    m_supportsDiagonalAdj = true;
}

QIcon LineTool::icon(const QColor &background, bool inEditor) const {
    Q_UNUSED(inEditor);
    return QIcon(iconPath(background) + "line.svg");
}
QString LineTool::name() const {
    return QStringLiteral("线条");
}

QString LineTool::nameID() {
    return QLatin1String("");
}

QString LineTool::description() const {
    return QStringLiteral("线条工具");
}

CaptureTool* LineTool::copy(QObject *parent) {
    return new LineTool(parent);
}

void LineTool::process(QPainter &painter, const QPixmap &pixmap, bool recordUndo) {
    if (recordUndo) {
        updateBackup(pixmap);
    }
    painter.setPen(QPen(m_color, m_thickness));
    painter.drawLine(m_points.first, m_points.second);
}

void LineTool::paintMousePreview(QPainter &painter, const CaptureContext &context) {
    painter.setPen(QPen(context.color, PADDING_VALUE + context.thickness));
    painter.drawLine(context.mousePos, context.mousePos);
}

void LineTool::drawStart(const CaptureContext &context) {
    m_color = context.color;
    m_thickness = context.thickness + PADDING_VALUE;
    m_points.first = context.mousePos;
    m_points.second = context.mousePos;
}

void LineTool::pressed(const CaptureContext &context) {
    Q_UNUSED(context);
}
