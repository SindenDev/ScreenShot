

#include "hovereventfilter.h"
#include <QEvent>

HoverEventFilter::HoverEventFilter(QObject *parent) : QObject(parent) {

}

bool HoverEventFilter::eventFilter(QObject *watched, QEvent *event) {
    QEvent::Type t = event->type();
    switch (t) {
    case QEvent::Enter:
        emit hoverIn(watched);
        break;
    case QEvent::Leave:
        emit hoverOut(watched);
        break;
    default:
        break;
    }
    return false;
}
