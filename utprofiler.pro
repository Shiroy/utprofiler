#-------------------------------------------------
#
# Project created by QtCreator 2014-04-26T12:18:34
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = utprofiler
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    uv.cpp \
    inscription.cpp \
    semestrecours.cpp \
    cursus.cpp \
    branche.cpp \
    profil.cpp \
    predicats.cpp \
    etudiant.cpp \
    autocompletion.cpp \
    utmanager.cpp \
    utstreamxml.cpp \
    utstream.cpp

HEADERS  += mainwindow.h \
    uv.h \
    inscription.h \
    semestrecours.h \
    cursus.h \
    branche.h \
    profil.h \
    predicats.h \
    etudiant.h \
    autocompletion.h \
    utprofilerexception.h \
    utmanager.h \
    utstreamxml.h \
    utstream.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    donne_test.xml
