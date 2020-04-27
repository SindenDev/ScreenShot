

#pragma once
#include <QColor>
#include <QStringList>
namespace GlobalValues {

int buttonBaseSize();

}


namespace ColorUtils { // namespace

bool colorIsDark(const QColor &c);

QColor contrastColor(const QColor &c);

} // namespace




namespace PathInfo { // namespace

const QString whiteIconPath();

const QString blackIconPath();

QStringList translationsPaths();

} // namespace


