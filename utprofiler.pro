#-------------------------------------------------
#
# Project created by QtCreator 2014-04-26T12:18:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = utprofiler
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    uv.cpp \
    uvmanager.cpp \
    uvstream.cpp \
    inscription.cpp

HEADERS  += mainwindow.h \
    uv.h \
    uvmanager.h \
    uvstream.h \
    inscription.h

FORMS    += mainwindow.ui
