

#pragma once

class QPixmap;
class QString;

class ScreenshotSaver {
public:
    ScreenshotSaver();

    void saveToClipboard(const QPixmap &capture);
    bool saveToFilesystem(const QPixmap &capture, const QString &path);
    bool saveToFilesystemGUI(const QPixmap &capture);

};
