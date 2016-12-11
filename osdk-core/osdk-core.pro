#-------------------------------------------------
#
# Project created by QtCreator 2016-11-25T20:53:09
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

include(osdk-core.pri)

TARGET = tst_coretest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_coretest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

DISTFILES += \
    osdk-core.pri \
    osdk-core-inc.pri
