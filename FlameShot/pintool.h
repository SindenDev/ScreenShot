

#pragma once

#include "abstractactiontool.h"

class PinTool : public AbstractActionTool {
    Q_OBJECT
public:
    explicit PinTool(QObject *parent = nullptr);

    bool closeOnButtonPressed() const;

    QIcon icon(const QColor &background, bool inEditor) const override;
    QString name() const override;
    static QString nameID();
    QString description() const override;

    QWidget* widget() override;

    CaptureTool* copy(QObject *parent = nullptr) override;

public slots:
    void pressed(const CaptureContext &context) override;

private:
    QRect m_geometry;
    QPixmap m_pixmap;
};
