#-------------------------------------------------
#
# Project created by QtCreator 2016-08-01T21:36:29
#
#-------------------------------------------------

QT       += core gui \
        webenginewidgets webchannel

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FileWatcher
TEMPLATE = app


SOURCES += main.cpp \
        MainWindow.cpp \
    FileWatcher.cpp \
    Directory.cpp \
    Action.cpp \
    ActionLinux.cpp \
    SettingWindow.cpp \
    Settings.cpp

HEADERS  += MainWindow.h \
    FileWatcher.h \
    Directory.h \
    Algorithm.h \
    Action.h \
    ActionLinux.h \
    SettingWindow.h \
    Settings.h

FORMS    += MainWindow.ui \
    SettingWindow.ui

RESOURCES += \
    resource.qrc

DISTFILES +=
