

#include "redotool.h"
#include <QPainter>

RedoTool::RedoTool(QObject *parent) : AbstractActionTool(parent) {

}

bool RedoTool::closeOnButtonPressed() const {
    return false;
}

QIcon RedoTool::icon(const QColor &background, bool inEditor) const {
    Q_UNUSED(inEditor);
    return QIcon(iconPath(background) + "redo-variant.svg");
}
QString RedoTool::name() const {
    return QStringLiteral("重做");
}

QString RedoTool::nameID() {
    return QLatin1String("");
}

QString RedoTool::description() const {
    return QStringLiteral("重做");
}

CaptureTool* RedoTool::copy(QObject *parent) {
    return new RedoTool(parent);
}

void RedoTool::pressed(const CaptureContext &context) {
    Q_UNUSED(context);
    emit requestAction(REQ_REDO_MODIFICATION);
}
