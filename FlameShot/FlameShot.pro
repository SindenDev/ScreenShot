#-------------------------------------------------
#
# Project created by QtCreator 2020-03-12T09:25:51
#
#-------------------------------------------------
win32:LIBS += -luser32 -lshell32
QT       += widgets network
QT  += dbus
CONFIG+=c++11

win32:CONFIG(release, debug|release):TARGET = FlameShot
else:win32:CONFIG(debug, debug|release):TARGET = FlameShotd

#DESTDIR = bin
TEMPLATE = lib



DEFINES += FLAMESHOT_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    abstractactiontool.cpp \
    abstractpathtool.cpp \
    abstracttwopointtool.cpp \
    arrowtool.cpp \
    blurtool.cpp \
    buttonhandler.cpp \
    capturebutton.cpp \
    capturecontext.cpp \
    capturerequest.cpp \
    capturewidget.cpp \
    circletool.cpp \
    color_utils.cpp \
    color_wheel.cpp \
    colorpicker.cpp \
    confighandler.cpp \
    controller.cpp \
    copytool.cpp \
    desktopinfo.cpp \
    exittool.cpp \
    filenamehandler.cpp \
    globalshortcutfilter.cpp \
    globalvalues.cpp \
    hovereventfilter.cpp \
    linetool.cpp \
    markertool.cpp \
    modificationcommand.cpp \
    movetool.cpp \
    notifierbox.cpp \
    penciltool.cpp \
    pintool.cpp \
    pinwidget.cpp \
    rectangletool.cpp \
    redotool.cpp \
    savetool.cpp \
    screengrabber.cpp \
    screenshotsaver.cpp \
    selectiontool.cpp \
    selectionwidget.cpp \
    sidepanelwidget.cpp \
    sizeindicatortool.cpp \
    systemnotification.cpp \
    textconfig.cpp \
    texttool.cpp \
    textwidget.cpp \
    toolfactory.cpp \
    undotool.cpp \
    utilitypanel.cpp

HEADERS += \
        flameshot_global.h \ 
    abstractactiontool.h \
    abstractpathtool.h \
    abstracttwopointtool.h \
    arrowtool.h \
    blurtool.h \
    buttonhandler.h \
    capturebutton.h \
    capturecontext.h \
    capturerequest.h \
    capturetool.h \
    capturewidget.h \
    circletool.h \
    color_utils.hpp \
    color_wheel.hpp \
    colorpicker.h \
    confighandler.h \
    controller.h \
    copytool.h \
    desktopinfo.h \
    exittool.h \
    filenamehandler.h \
    globalshortcutfilter.h \
    globalvalues.h \
    hovereventfilter.h \
    linetool.h \
    markertool.h \
    modificationcommand.h \
    movetool.h \
    notifierbox.h \
    penciltool.h \
    pintool.h \
    pinwidget.h \
    rectangletool.h \
    redotool.h \
    savetool.h \
    screengrabber.h \
    screenshotsaver.h \
    selectiontool.h \
    selectionwidget.h \
    sidepanelwidget.h \
    sizeindicatortool.h \
    systemnotification.h \
    textconfig.h \
    texttool.h \
    textwidget.h \
    toolfactory.h \
    undotool.h \
    utilitypanel.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    graphics.qrc
