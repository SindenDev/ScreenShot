

#pragma once

#include "abstracttwopointtool.h"

class SelectionTool : public AbstractTwoPointTool {
    Q_OBJECT
public:
    explicit SelectionTool(QObject *parent = nullptr);

    bool closeOnButtonPressed() const;

    QIcon icon(const QColor &background, bool inEditor) const override;
    QString name() const override;
    static QString nameID();
    QString description() const override;

    CaptureTool* copy(QObject *parent = nullptr) override;
    void process(
            QPainter &painter, const QPixmap &pixmap, bool recordUndo = false) override;
    void paintMousePreview(QPainter &painter, const CaptureContext &context) override;

public slots:
    void drawStart(const CaptureContext &context) override;
    void pressed(const CaptureContext &context) override;
};
