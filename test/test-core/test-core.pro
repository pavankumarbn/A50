#-------------------------------------------------
#
# Project created by QtCreator 2016-11-29T22:23:16
#
#-------------------------------------------------

QT       += testlib core gui

TARGET = tst_coretest
CONFIG   += console

TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += tst_coretest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

include(../../osdk-core/osdk-core.pri)
include(../../platform/qt/QonboardSDK.pri))

HEADERS += \
    ../cmdline.h

INCLUDEPATH += \
    ../
