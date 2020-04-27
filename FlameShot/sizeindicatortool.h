

#pragma once

#include "abstractactiontool.h"

class SizeIndicatorTool : public AbstractActionTool {
    Q_OBJECT
public:
    explicit SizeIndicatorTool(QObject *parent = nullptr);

    bool closeOnButtonPressed() const;

    QIcon icon(const QColor &background, bool inEditor) const override;
    QString name() const override;
    static QString nameID();
    QString description() const override;

    CaptureTool* copy(QObject *parent = nullptr) override;

public slots:
    void pressed(const CaptureContext &context) override;
};
