#-------------------------------------------------
#
# Project created by QtCreator 2015-04-15T09:28:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = particles
TEMPLATE = app


SOURCES += main.cpp\
    widget.cpp \
    magnets.cpp

HEADERS  += widget.h \
    magnets.h

FORMS    += widget.ui \
    magnets.ui \
    display.ui

QMAKE_LFLAGS    += /INCREMENTAL:NO
