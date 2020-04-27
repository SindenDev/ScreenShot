

#include "copytool.h"
#include "screenshotsaver.h"
#include <QPainter>

CopyTool::CopyTool(QObject *parent) : AbstractActionTool(parent) {

}

bool CopyTool::closeOnButtonPressed() const {
    return true;
}

QIcon CopyTool::icon(const QColor &background, bool inEditor) const {
    Q_UNUSED(inEditor);
    return QIcon(iconPath(background) + "content-copy.svg");
}
QString CopyTool::name() const {
    return QStringLiteral("复制");
}

QString CopyTool::nameID() {
    return QLatin1String("");
}

QString CopyTool::description() const {
    return QStringLiteral("复制到剪贴板中");
}

CaptureTool* CopyTool::copy(QObject *parent) {
    return new CopyTool(parent);
}

void CopyTool::pressed(const CaptureContext &context) {
    emit requestAction(REQ_CAPTURE_DONE_OK);
    ScreenshotSaver().saveToClipboard(context.selectedScreenshotArea());
}
