#-------------------------------------------------
#
# Project created by QtCreator 2017-05-24T23:51:26
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled1
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    data.cpp \
    myserver.cpp

HEADERS  += widget.h \
    data.h \
    myserver.h

FORMS    += widget.ui
