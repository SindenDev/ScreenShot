

#pragma once

#include <QWidget>

class ColorPicker : public QWidget {
    Q_OBJECT
public:
    explicit ColorPicker(QWidget *parent = nullptr);

    QColor drawColor();

    void show();
    void hide();

signals:
    void colorSelected(QColor c);

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);

    QVector<QRect> handleMask() const;

private:
    int m_colorAreaSize;
    QVector<QRect> m_colorAreaList;
    QVector<QColor> m_colorList;

    QColor m_uiColor, m_drawColor;
};
