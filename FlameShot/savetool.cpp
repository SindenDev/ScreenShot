

#include "savetool.h"
#include "screenshotsaver.h"
#include <QPainter>
#include <QDebug>
SaveTool::SaveTool(QObject *parent) : AbstractActionTool(parent) {

}

bool SaveTool::closeOnButtonPressed() const {
    return true;
}

QIcon SaveTool::icon(const QColor &background, bool inEditor) const {
    Q_UNUSED(inEditor);
    return QIcon(iconPath(background) + "content-save.svg");
}
QString SaveTool::name() const {
    return QStringLiteral("����");
}

QString SaveTool::nameID() {
    return QLatin1String("");
}

QString SaveTool::description() const {
    return QStringLiteral("�����ͼ");
}

CaptureTool* SaveTool::copy(QObject *parent) {
    return new SaveTool(parent);
}

void SaveTool::pressed(const CaptureContext &context) {
    if (context.savePath.isEmpty()) {
        emit requestAction(REQ_HIDE_GUI);
        bool ok = ScreenshotSaver().saveToFilesystemGUI(
                    context.selectedScreenshotArea());
        if (ok) {
            emit requestAction(REQ_CAPTURE_DONE_OK);
        }
    } else {
        bool ok = ScreenshotSaver().saveToFilesystem(
                    context.selectedScreenshotArea(), context.savePath);
        if (ok) {
            emit requestAction(REQ_CAPTURE_DONE_OK);
        }
    }
}
