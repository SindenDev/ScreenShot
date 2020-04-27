

#include "pintool.h"
#include "pinwidget.h"

PinTool::PinTool(QObject *parent) : AbstractActionTool(parent) {

}

bool PinTool::closeOnButtonPressed() const {
    return true;
}

QIcon PinTool::icon(const QColor &background, bool inEditor) const {
    Q_UNUSED(inEditor);
    return QIcon(iconPath(background) + "pin.svg");
}
QString PinTool::name() const {
    return QStringLiteral("大头针工具");
}

QString PinTool::nameID() {
    return QLatin1String("");
}

QString PinTool::description() const {
    return QStringLiteral("大头针工具");
}

QWidget* PinTool::widget() {
    PinWidget *w = new PinWidget(m_pixmap);
    const int &&m = w->margin();
    QRect adjusted_pos = m_geometry + QMargins(m, m, m, m);
    w->setGeometry(adjusted_pos);
    return w;
}

CaptureTool* PinTool::copy(QObject *parent) {
    return new PinTool(parent);
}

void PinTool::pressed(const CaptureContext &context) {
    emit requestAction(REQ_CAPTURE_DONE_OK);
    m_geometry = context.selection;
    m_geometry.setTopLeft(m_geometry.topLeft() + context.widgetOffset);
    m_pixmap = context.selectedScreenshotArea();
    emit requestAction(REQ_ADD_EXTERNAL_WIDGETS);

}
