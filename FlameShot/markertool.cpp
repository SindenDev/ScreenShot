

#include "markertool.h"
#include <QPainter>

namespace {

#define PADDING_VALUE 14

}

MarkerTool::MarkerTool(QObject *parent) : AbstractTwoPointTool(parent) {
    m_supportsOrthogonalAdj = true;
    m_supportsDiagonalAdj = true;
}

QIcon MarkerTool::icon(const QColor &background, bool inEditor) const {
    Q_UNUSED(inEditor);
    return QIcon(iconPath(background) + "marker.svg");
}
QString MarkerTool::name() const {
    return QStringLiteral("标记");
}

QString MarkerTool::nameID() {
    return QLatin1String("");
}

QString MarkerTool::description() const {
    return QStringLiteral("标记");
}

CaptureTool* MarkerTool::copy(QObject *parent) {
    return new MarkerTool(parent);
}

void MarkerTool::process(QPainter &painter, const QPixmap &pixmap, bool recordUndo) {
    if (recordUndo) {
        updateBackup(pixmap);
    }
    painter.setCompositionMode(QPainter::CompositionMode_Multiply);
    painter.setOpacity(0.35);
    painter.setPen(QPen(m_color, m_thickness));
    painter.drawLine(m_points.first, m_points.second);
}

void MarkerTool::paintMousePreview(QPainter &painter, const CaptureContext &context) {
    painter.setCompositionMode(QPainter::CompositionMode_Multiply);
    painter.setOpacity(0.35);
    painter.setPen(QPen(context.color, PADDING_VALUE + context.thickness));
    painter.drawLine(context.mousePos, context.mousePos);
}

void MarkerTool::drawStart(const CaptureContext &context) {
    m_color = context.color;
    m_thickness = context.thickness + PADDING_VALUE;
    m_points.first = context.mousePos;
    m_points.second = context.mousePos;
}

void MarkerTool::pressed(const CaptureContext &context) {
    Q_UNUSED(context);
}

void MarkerTool::thicknessChanged(const int th) {
    m_thickness = th + PADDING_VALUE;
}
