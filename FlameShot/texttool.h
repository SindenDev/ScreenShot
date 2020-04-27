

#pragma once

#include "capturetool.h"
#include <QPointer>

class TextWidget;
class TextConfig;

class TextTool : public CaptureTool {
    Q_OBJECT
public:
    explicit TextTool(QObject *parent = nullptr);

    bool isValid() const override;
    bool closeOnButtonPressed() const override;
    bool isSelectable() const override;
    bool showMousePreview() const override;

    QIcon icon(const QColor &background,
                       bool inEditor) const override;
    QString name() const override;
    static QString nameID();
    QString description() const override;

    QWidget* widget() override;
    QWidget* configurationWidget() override;
    CaptureTool* copy(QObject *parent = nullptr) override;

    void undo(QPixmap &pixmap) override;
    void process(
            QPainter &painter, const QPixmap &pixmap, bool recordUndo = false) override;
    void paintMousePreview(QPainter &painter, const CaptureContext &context) override;

public slots:
    void drawEnd(const QPoint &p) override;
    void drawMove(const QPoint &p) override;
    void drawStart(const CaptureContext &context) override;
    void pressed(const CaptureContext &context) override;
    void colorChanged(const QColor &c) override;
    void thicknessChanged(const int th) override;

private slots:
    void updateText(const QString &s);
    void setFont(const QFont &f);
    void updateFamily(const QString &s);
    void updateFontUnderline(const bool underlined);
    void updateFontStrikeOut(const bool s);
    void updateFontWeight(const QFont::Weight w);
    void updateFontItalic(const bool italic);

private:
    QFont m_font;
    QString m_text;
    int m_size;
    QColor m_color;
    QPixmap m_pixmapBackup;
    QRect m_backupArea;
    QPointer<TextWidget> m_widget;
    QPointer<TextConfig> m_confW;
};
