#-------------------------------------------------
#
# Project created by QtCreator 2019-06-20T23:30:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MtGui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    monsterinfolist.cpp \
    monsterinfolistitem.cpp \
    mt.cpp \
    storewindow.cpp \
    variables.cpp

HEADERS  += mainwindow.h \
    monsterinfolist.h \
    monsterinfolistitem.h \
    mt.h \
    storewindow.h \
    total.h \
    variables.h

FORMS    += mainwindow.ui \
    storewindow.ui

RESOURCES += \
    mtgraphics.qrc
