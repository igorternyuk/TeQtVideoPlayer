#-------------------------------------------------
#
# Project created by QtCreator 2017-11-02T16:06:07
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++1z
TARGET = TeQtVideoPlayer
TEMPLATE = app
DEFINES += DEBUG

SOURCES += main.cpp\
        mainwindow.cpp \
    videowidget.cpp \
    playlistwindow.cpp \
    settingsutil.cpp

HEADERS  += mainwindow.h \
    videowidget.h \
    playlistwindow.h \
    settingsutil.h

FORMS    += mainwindow.ui \
    playlistwindow.ui

RESOURCES += \
    resources.qrc
