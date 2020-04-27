

#include "sizeindicatortool.h"
#include <QPainter>

SizeIndicatorTool::SizeIndicatorTool(QObject *parent) : AbstractActionTool(parent) {

}

bool SizeIndicatorTool::closeOnButtonPressed() const {
    return false;
}

QIcon SizeIndicatorTool::icon(const QColor &background, bool inEditor) const {
    return inEditor ? QIcon() :
                      QIcon(iconPath(background) + "size_indicator.svg");
}
QString SizeIndicatorTool::name() const {
    return QStringLiteral("��ͼ�����С");
}

QString SizeIndicatorTool::nameID() {
    return QLatin1String("");
}

QString SizeIndicatorTool::description() const {
    return QStringLiteral("��ͼ�����С(X��Y)");
}

CaptureTool* SizeIndicatorTool::copy(QObject *parent) {
    return new SizeIndicatorTool(parent);
}

void SizeIndicatorTool::pressed(const CaptureContext &context) {
    Q_UNUSED(context);
}
