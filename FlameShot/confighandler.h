
#pragma once

#include "capturebutton.h"
#include <QVector>
#include <QSettings>

class ConfigHandler {
public:
    explicit ConfigHandler();

    QVector<CaptureButton::ButtonType> getButtons();
    void setButtons(const QVector<CaptureButton::ButtonType> &);

    QVector<QColor> getUserColors();
    void setUserColors(const QVector<QColor> &);

    QString savePathValue();
    void setSavePath(const QString &);

    QColor uiMainColorValue();
    void setUIMainColor(const QColor &);

    QColor uiContrastColorValue();
    void setUIContrastColor(const QColor &);

    QColor drawColorValue();
    void setDrawColor(const QColor &);

    bool showHelpValue();
    void setShowHelp(const bool);

    bool desktopNotificationValue();
    void setDesktopNotification(const bool);

    QString filenamePatternValue();
    void setFilenamePattern(const QString &);

    bool disabledTrayIconValue();
    void setDisabledTrayIcon(const bool);

    int drawThicknessValue();
    void setdrawThickness(const int);

    bool keepOpenAppLauncherValue();
    void setKeepOpenAppLauncher(const bool);

    bool verifyLaunchFile();
    bool startupLaunchValue();
    void setStartupLaunch(const bool);

    int contrastOpacityValue();
    void setContrastOpacity(const int);

    bool closeAfterScreenshotValue();
    void setCloseAfterScreenshot(const bool);

    bool copyAndCloseAfterUploadEnabled();
    void setCopyAndCloseAfterUploadEnabled(const bool);


    void setDefaults();
    void setAllTheButtons();

    QString configFilePath() const;

private:
    QSettings m_settings;

    bool normalizeButtons(QVector<int> &);

    QVector<CaptureButton::ButtonType> fromIntToButton(const QVector<int> &l);
    QVector<int> fromButtonToInt(const QVector<CaptureButton::ButtonType> &l);
};
