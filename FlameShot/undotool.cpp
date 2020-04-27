

#include "undotool.h"
#include <QPainter>

UndoTool::UndoTool(QObject *parent) : AbstractActionTool(parent) {

}

bool UndoTool::closeOnButtonPressed() const {
    return false;
}

QIcon UndoTool::icon(const QColor &background, bool inEditor) const {
    Q_UNUSED(inEditor);
    return QIcon(iconPath(background) + "undo-variant.svg");
}
QString UndoTool::name() const {
    return QStringLiteral("³·Ïú");
}

QString UndoTool::nameID() {
    return QLatin1String("");
}

QString UndoTool::description() const {
    return QStringLiteral("³·Ïû");
}

CaptureTool* UndoTool::copy(QObject *parent) {
    return new UndoTool(parent);
}

void UndoTool::pressed(const CaptureContext &context) {
    Q_UNUSED(context);
    emit requestAction(REQ_UNDO_MODIFICATION);
}
