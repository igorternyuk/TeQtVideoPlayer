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


SOURCES += main.cpp\
        mainwindow.cpp \
    videowidget.cpp

HEADERS  += mainwindow.h \
    videowidget.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
