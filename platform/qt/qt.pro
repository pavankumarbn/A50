QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = qt

TEMPLATE = app

include(QonboardSDK.pri))

SOURCES += main.cpp

DISTFILES += \
    QonboardSDK.pri
