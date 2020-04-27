

#include "movetool.h"
#include <QPainter>

MoveTool::MoveTool(QObject *parent) : AbstractActionTool(parent) {

}

bool MoveTool::closeOnButtonPressed() const {
    return false;
}

QIcon MoveTool::icon(const QColor &background, bool inEditor) const {
    Q_UNUSED(inEditor);
    return QIcon(iconPath(background) + "cursor-move.svg");
}
QString MoveTool::name() const {
    return QStringLiteral("移动");
}

QString MoveTool::nameID() {
    return QLatin1String("");
}

QString MoveTool::description() const {
    return QStringLiteral("移动选中区域");
}

CaptureTool* MoveTool::copy(QObject *parent) {
    return new MoveTool(parent);
}

void MoveTool::pressed(const CaptureContext &context) {
    Q_UNUSED(context);
    emit requestAction(REQ_MOVE_MODE);
}
