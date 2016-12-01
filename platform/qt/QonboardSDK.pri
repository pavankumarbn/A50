include(../../osdk-core/osdk-core.pri))
QT += serialport
SOURCES += \
    $$PWD/src/DJI_HardDriver_Qt.cpp

HEADERS += \
    $$PWD/inc/DJI_HardDriver_Qt.h

INCLUDEPATH += $$PWD/inc
