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
    opcjerys.cpp \
    generate.cpp \
    magnesy.cpp \
    global.cpp \
    liczenie.cpp

HEADERS  += \
    wczytaj.h \
    mainwindow.h \
    opcjerys.h \
    generate.h \
    magnesy.h \
    global.h \
    liczenie.h

FORMS    += mainwindow.ui \
    wczytaj.ui \
    opcjerys.ui \
    liczenie.ui
