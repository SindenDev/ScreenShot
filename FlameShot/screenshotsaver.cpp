

#include "screenshotsaver.h"
#include "systemnotification.h"
#include "filenamehandler.h"
#include "confighandler.h"
#include <QClipboard>
#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QImageWriter>

ScreenshotSaver::ScreenshotSaver() {
}

void ScreenshotSaver::saveToClipboard(const QPixmap &capture) {
    SystemNotification().sendMessage(
                QStringLiteral("��ͼ���浽������"));
    QApplication::clipboard()->setPixmap(capture);
}

bool ScreenshotSaver::saveToFilesystem(const QPixmap &capture,
                                       const QString &path)
{
    QString completePath = FileNameHandler().generateAbsolutePath(path);
    completePath += QLatin1String(".png");
    bool ok = capture.save(completePath);
    QString saveMessage;
    QString notificationPath = completePath;

    if (ok) {
        ConfigHandler().setSavePath(path);
        saveMessage = QStringLiteral("��ͼ���Ϊ ") + completePath;
    } else {
        saveMessage = QStringLiteral("������ ") + completePath;
        notificationPath = "";
    }

    SystemNotification().sendMessage(saveMessage, notificationPath);
    return ok;
}

bool ScreenshotSaver::saveToFilesystemGUI(const QPixmap &capture) {
    bool ok = false;

    while (!ok) {
        QString savePath = QFileDialog::getSaveFileName(
                    nullptr,
                    QString(),
                    FileNameHandler().absoluteSavePath() + ".png",
					QLatin1String("Portable Network Graphic file (PNG) (*.png);;BMP file (*.bmp);;JPEG file (*.jpg)"));

        if (savePath.isNull()) {
            break;
        }

	if (!savePath.endsWith(QLatin1String(".png"), Qt::CaseInsensitive) &&
	    !savePath.endsWith(QLatin1String(".bmp"), Qt::CaseInsensitive) &&
	    !savePath.endsWith(QLatin1String(".jpg"), Qt::CaseInsensitive)) {

	    savePath += QLatin1String(".png");
	}

        ok = capture.save(savePath);

        if (ok) {
            QString pathNoFile = savePath.left(savePath.lastIndexOf(QLatin1String("/")));
            ConfigHandler().setSavePath(pathNoFile);
            QString msg = QStringLiteral("��ͼ���Ϊ ") + savePath;
            SystemNotification().sendMessage(msg, savePath);
        } else {
            QString msg = QStringLiteral("������ ") + savePath;
            QMessageBox saveErrBox(
                        QMessageBox::Warning,
                        QStringLiteral("�������"),
                        msg);
            saveErrBox.setWindowIcon(QIcon(":img/app/flameshot.svg"));
            saveErrBox.exec();
        }
    }
    return ok;
}
