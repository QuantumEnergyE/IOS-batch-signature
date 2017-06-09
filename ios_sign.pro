#-------------------------------------------------
#
# Project created by QtCreator 2017-02-23T10:47:05
#
#-------------------------------------------------

QT       += core gui
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ios_sign
TEMPLATE = app


SOURCES += main.cpp\
        signature.cpp \
    tablemodel.cpp \
    tabledelegate.cpp

HEADERS  += signature.h \
    tablemodel.h \
    tabledelegate.h

FORMS    += signature.ui
