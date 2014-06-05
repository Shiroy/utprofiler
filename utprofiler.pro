#-------------------------------------------------
#
# Project created by QtCreator 2014-04-26T12:18:34
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = utprofiler
TEMPLATE = app

unix{
    QMAKE_CXXFLAGS += -std=c++11
}

win32{
    QMAKE_CXXFLAGS= -std=c++0x -U__STRICT_ANSI__ -Doverride="" -Dnoexcept="throw()"
}

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
    utstream.cpp \
    uvsearchmodel.cpp \
    uv_editor.cpp \
    etudiantstream.cpp \
    etudiantstreamxml.cpp \
    branche_viewer.cpp \
    branche_editor.cpp


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
    utstream.h \
    uvsearchmodel.h \
    uv_editor.h \
    etudiantstream.h \
    etudiantstreamxml.h \
    branche_viewer.h \
    branche_editor.h

FORMS    += mainwindow.ui \
    uv_editor.ui \
    branche_viewer.ui \
    branche_editor.ui



OTHER_FILES += \
    donne_test.xml \
    donne2_test.xml \
    antoine_wacheux.xml
