

#include "exittool.h"
#include <QPainter>

ExitTool::ExitTool(QObject *parent) : AbstractActionTool(parent) {

}

bool ExitTool::closeOnButtonPressed() const {
    return true;
}

QIcon ExitTool::icon(const QColor &background, bool inEditor) const {
    Q_UNUSED(inEditor);
    return QIcon(iconPath(background) + "close.svg");
}
QString ExitTool::name() const {
    return QStringLiteral("ÍË³ö");
}

QString ExitTool::nameID() {
    return QLatin1String("");
}

QString ExitTool::description() const {
    return QStringLiteral("ÍË³ö");
}

CaptureTool* ExitTool::copy(QObject *parent) {
    return new ExitTool(parent);
}

void ExitTool::pressed(const CaptureContext &context) {
    Q_UNUSED(context);
    emit requestAction(REQ_CLOSE_GUI);
}
