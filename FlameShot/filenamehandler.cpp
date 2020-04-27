
#include "filenamehandler.h"
#include "confighandler.h"
#include <ctime>
#include <locale>
#include <QStandardPaths>
#include <QDir>

FileNameHandler::FileNameHandler(QObject *parent) : QObject(parent) {
    std::locale::global(std::locale(""));
}

QString FileNameHandler::parsedPattern() {
    return parseFilename(ConfigHandler().filenamePatternValue());
}

QString FileNameHandler::parseFilename(const QString &name) {
    QString res = name;
    if (name.isEmpty()) {
        res = QLatin1String("%F_%H-%M");
    }
    std::time_t t = std::time(NULL);

    char *tempData = QStringTocharArr(res);
    char data[MAX_CHARACTERS] = {0};
    std::strftime(data, sizeof(data),
                  tempData, std::localtime(&t));
    res = QString::fromLocal8Bit(data, (int)strlen(data));
    free(tempData);

    // add the parsed pattern in a correct format for the filesystem
    res = res.replace(QLatin1String("/"), QStringLiteral("/")).replace(QLatin1String(":"), QLatin1String("-"));
    return res;
}

QString FileNameHandler::generateAbsolutePath(const QString &path) {
    QString directory = path;
    QString filename = parsedPattern();
    fixPath(directory, filename);
    return directory + filename;
}
// path a images si no existe, add numeration
void FileNameHandler::setPattern(const QString &pattern) {
    ConfigHandler().setFilenamePattern(pattern);
}

QString FileNameHandler::absoluteSavePath(QString &directory, QString &filename) {
    ConfigHandler config;
    directory = config.savePathValue();
    if (directory.isEmpty() || !QDir(directory).exists() || !QFileInfo(directory).isWritable()) {
        directory = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    }
    filename = parsedPattern();
    fixPath(directory, filename);
    return directory + filename;
}

QString FileNameHandler::absoluteSavePath() {
    QString dir, file;
    return absoluteSavePath(dir, file);
}

QString FileNameHandler::charArrToQString(const char *c) {
    return QString::fromLocal8Bit(c, MAX_CHARACTERS);
}

char * FileNameHandler::QStringTocharArr(const QString &s) {
    QByteArray ba = s.toLocal8Bit();
    return const_cast<char *>(strdup(ba.constData()));
}

void FileNameHandler::fixPath(QString &directory, QString &filename) {
    if (!directory.endsWith(QLatin1String("/"))) {
        directory += QLatin1String("/");
    }

    QFileInfo checkFile(directory + filename + ".png");
    if (checkFile.exists()) {
        filename += QLatin1String("_");
        int i = 1;
        while (true) {
            checkFile.setFile(
                        directory + filename + QString::number(i) + ".png");
            if (!checkFile.exists()) {
                filename += QString::number(i);
                break;
            }
            ++i;
        }
    }
}
