
#pragma once

#include "capturebutton.h"
#include <QVector>
#include <QObject>
#include <QRegion>

class CaptureButton;
class QRect;
class QPoint;

class ButtonHandler : public QObject {
    Q_OBJECT
public:
    ButtonHandler(const QVector<CaptureButton*>&, QObject *parent = nullptr);
    explicit ButtonHandler(QObject *parent = nullptr);

    void hideSectionUnderMouse(const QPoint &p);

    bool isVisible() const;
    bool buttonsAreInside() const;
    size_t size() const;

    void setButtons(const QVector<CaptureButton*>);
    bool contains(const QPoint &p) const;
    void updateScreenRegions(const QVector<QRect> &rects);
    void updateScreenRegions(const QRect &rect);

public slots:
    void updatePosition(const QRect &selection);
    void hide();
    void show();

private:
    QVector<QPoint> horizontalPoints(const QPoint &center, const int elements,
                               const bool leftToRight) const;
    QVector<QPoint> verticalPoints(const QPoint &center, const int elements,
                               const bool upToDown) const;

    QRect intersectWithAreas(const QRect &rect);

    QVector<CaptureButton*> m_vectorButtons;

    QRegion m_screenRegions;

    QRect m_selection;

    int m_separator;
    int m_buttonExtendedSize;
    int m_buttonBaseSize;

    bool m_buttonsAreInside;
    bool m_blockedRight;
    bool m_blockedLeft;
    bool m_blockedBotton;
    bool m_blockedTop;
    bool m_oneHorizontalBlocked;
    bool m_horizontalyBlocked;
    bool m_allSidesBlocked;

    // aux methods
    void init();
    void resetRegionTrack();
    void updateBlockedSides();
    void expandSelection();
    void positionButtonsInside(int index);
    void ensureSelectionMinimunSize();
    void moveButtonsToPoints(const QVector<QPoint> &points, int &index);
    void adjustHorizontalCenter(QPoint &center);
};
