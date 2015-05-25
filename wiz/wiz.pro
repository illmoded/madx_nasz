#-------------------------------------------------
#
# Project created by QtCreator 2015-05-25T09:08:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = wiz
TEMPLATE = app
CONFIG += c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    wczytaj.cpp \
    dodaj.cpp

HEADERS  += \
    wczytaj.h \
    dodaj.h \
    mainwindow.h

FORMS    += mainwindow.ui \
    wczytaj.ui \
    dodaj.ui
