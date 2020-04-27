
#pragma once

#include <QTextEdit>

class TextWidget : public QTextEdit
{
    Q_OBJECT
public:
    explicit TextWidget(QWidget *parent = nullptr);

    void adjustSize();
    void setFont(const QFont &f);

protected:
    void showEvent(QShowEvent *e);
    void resizeEvent(QResizeEvent *e);

signals:
    void textUpdated(const QString &s);

public slots:
    void updateFont(const QFont &f);
    void setTextColor(const QColor &c);
    void setFontPointSize(qreal s);

private slots:
    void emitTextUpdated();

private:
    QSize m_baseSize;
    QSize m_minSize;
};
