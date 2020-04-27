

#pragma once

#include <QObject>

class HoverEventFilter : public QObject
{
    Q_OBJECT
public:
    explicit HoverEventFilter(QObject *parent = nullptr);

signals:
    void hoverIn(QObject *);
    void hoverOut(QObject *);

protected:
    bool eventFilter(QObject *watched, QEvent *event);
};
