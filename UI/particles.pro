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
    magnets.cpp \
    sdialog.cpp \
    dodaj.cpp

HEADERS  += widget.h \
    magnets.h \
    sdialog.h \
    dodaj.h

FORMS    += widget.ui \
    magnets.ui \
    display.ui \
    sdialog.ui \
    dodaj.ui

QMAKE_LFLAGS    += /INCREMENTAL:NO
