
#include <QColor>
#include <qmath.h>

namespace color_widgets {
namespace detail {


inline qreal color_chromaF(const QColor& c)
{
    qreal max = qMax(c.redF(), qMax(c.greenF(), c.blueF()));
    qreal min = qMin(c.redF(), qMin(c.greenF(), c.blueF()));
    return max - min;
}

inline qreal color_lumaF(const QColor& c)
{
    return 0.30 * c.redF() + 0.59 * c.greenF() + 0.11 * c.blueF();
}
QColor color_from_lch(qreal hue, qreal chroma, qreal luma, qreal alpha = 1 );

inline QColor rainbow_lch(qreal hue)
{
    return color_from_lch(hue,1,1);
}

inline QColor rainbow_hsv(qreal hue)
{
    return QColor::fromHsvF(hue,1,1);
}

inline qreal color_lightnessF(const QColor& c)
{
    return ( qMax(c.redF(),qMax(c.greenF(),c.blueF())) +
             qMin(c.redF(),qMin(c.greenF(),c.blueF())) ) / 2;
}

inline qreal color_HSL_saturationF(const QColor& col)
{
    qreal c = color_chromaF(col);
    qreal l = color_lightnessF(col);
    if ( qFuzzyCompare(l+1,1) || qFuzzyCompare(l+1,2) )
        return 0;
    return c / (1-qAbs(2*l-1));
}

QColor color_from_hsl(qreal hue, qreal sat, qreal lig, qreal alpha = 1 );

} // namespace detail
} // namespace color_widgets
