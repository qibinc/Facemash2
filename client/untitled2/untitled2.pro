#-------------------------------------------------
#
# Project created by QtCreator 2017-05-25T00:30:39
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled2
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    data.cpp \
    myclient.cpp

HEADERS  += widget.h \
    data.h \
    myclient.h

FORMS    += widget.ui
