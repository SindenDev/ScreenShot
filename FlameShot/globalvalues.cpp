

#include "globalvalues.h"
#include <QFontMetrics>
#include <QApplication>
#include <QFileInfo>
#include <QDir>
int GlobalValues::buttonBaseSize() {
    return QApplication::fontMetrics().lineSpacing() * 2.2;
}


inline qreal getColorLuma(const QColor &c) {
    return 0.30 * c.redF() + 0.59 * c.greenF() + 0.11 * c.blueF();
}

bool ColorUtils::colorIsDark(const QColor &c) {
    bool isWhite = false;
    if (getColorLuma(c) <= 0.60) {
        isWhite = true;
    }
    return isWhite;
}

QColor ColorUtils::contrastColor(const QColor &c) {
    int change = colorIsDark(c) ? 30 : -45;

    return QColor(qBound(0, c.red() + change, 255),
                  qBound(0, c.green() + change, 255),
                  qBound(0, c.blue() + change, 255));
}

const QString PathInfo::whiteIconPath() {
    return QStringLiteral(":/img/material/white/");
}

const QString PathInfo::blackIconPath() {
    return QStringLiteral(":/img/material/black/");
}

QStringList PathInfo::translationsPaths() {
    QString binaryPath = QFileInfo(qApp->applicationDirPath())
            .absoluteFilePath();
    QString trPath = QDir::toNativeSeparators(binaryPath + "/translations") ;
#if defined(Q_OS_LINUX) || defined(Q_OS_UNIX)
    return QStringList()
            << QStringLiteral(APP_PREFIX) + "/share/flameshot/translations"
            << trPath
            << QStringLiteral("/usr/share/flameshot/translations")
            << QStringLiteral("/usr/local/share/flameshot/translations");
#elif defined(Q_OS_WIN)
    return QStringList()
            << trPath;
#endif
}
