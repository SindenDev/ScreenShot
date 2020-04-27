

#include "utilitypanel.h"
#include <QPropertyAnimation>
#include <QVBoxLayout>
#include <QTimer>
#include <QScrollArea>
#include <QWheelEvent>

UtilityPanel::UtilityPanel(QWidget *parent) : QWidget(parent) {
    initInternalPanel();
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setCursor(Qt::ArrowCursor);

    m_showAnimation = new QPropertyAnimation(m_internalPanel, "geometry", this);
    m_showAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    m_showAnimation->setDuration(300);

    m_hideAnimation = new QPropertyAnimation(m_internalPanel, "geometry", this);
    m_hideAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    m_hideAnimation->setDuration(300);

    connect(m_hideAnimation, &QPropertyAnimation::finished,
            m_internalPanel, &QWidget::hide);
}

QWidget *UtilityPanel::toolWidget() const {
    return m_toolWidget;
}

void UtilityPanel::addToolWidget(QWidget *w) {
    if (m_toolWidget) {
        m_toolWidget->deleteLater();
    }
    if (w) {
        m_toolWidget = w;
        m_upLayout->addWidget(w);
    }
}

void UtilityPanel::clearToolWidget() {
    if (m_toolWidget) {
        m_toolWidget->deleteLater();
    }
}

void UtilityPanel::pushWidget(QWidget *w) {
    m_layout->addWidget(w);
}

void UtilityPanel::toggle() {
    if (m_internalPanel->isHidden()) {
        setAttribute(Qt::WA_TransparentForMouseEvents, false);
        m_showAnimation->setStartValue(QRect(-width(), 0, 0, height()));
        m_showAnimation->setEndValue(QRect(0, 0, width(), height()));
        m_internalPanel->show();
        m_showAnimation->start();
    } else {
        setAttribute(Qt::WA_TransparentForMouseEvents);
        m_hideAnimation->setStartValue(QRect(0, 0, width(), height()));
        m_hideAnimation->setEndValue(QRect(-width(), 0, 0, height()));
        m_hideAnimation->start();
    }
}

void UtilityPanel::initInternalPanel() {
    m_internalPanel = new QScrollArea(this);
    m_internalPanel->setAttribute(Qt::WA_NoMousePropagation);
    QWidget *widget = new QWidget();
    m_internalPanel->setWidget(widget);
    m_internalPanel->setWidgetResizable(true);

    m_layout = new QVBoxLayout();
    m_upLayout = new QVBoxLayout();
    m_layout->addLayout(m_upLayout);
    widget->setLayout(m_layout);

    QColor bgColor = palette().background().color();
    bgColor.setAlphaF(0.0);
    m_internalPanel->setStyleSheet(QStringLiteral("QScrollArea {background-color: %1}")
                                   .arg(bgColor.name()));
    m_internalPanel->hide();
}
