#-------------------------------------------------
#
# Project created by QtCreator 2015-11-23T16:26:43
#
#-------------------------------------------------

TARGET = onboardSDK
TEMPLATE = app

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


#-------------------------------------------------
#
# Project management
#
#-------------------------------------------------


HEADERS  += djionboardsdk.h \
            SDKWidgets.h \
    autotest.h \
    qwaypoints.h \
    mfiopannel.h \
    recorder.h

SOURCES += main.cpp\
           djionboardsdk.cpp \
    autotest.cpp \
    qwaypoints.cpp \
    mfiopannel.cpp \
    recorder.cpp

DJILIB += ONBOARDSDK\
          #GROUNDSTATION\
          DJILIBCORE

DEPENDENCE += QT\
              DJILIB\
              DEPENDENCE

DEFINES += $$DEPENDENCE

#DEV += SDK_DEV

contains(DEV,SDK_DEV){
DEFINES += SDK_DEV
message("DEV Branch")
SOURCES += uidev.cpp \
           ../../../lib/FOS/src/buffer.cpp \
           ../../../lib/RCOS/src/rc.cpp \
           ../../../lib/RCOS/src/rcGraph.cpp \
           ../../../lib/RCOS/src/rcHardDriver.cpp \
           ../../../lib/DBI/src/DBI.cpp \
           ../../../lib/DBI/src/DBIShadow.cpp \
           ../../../lib/swarm/src/Swarm.cpp \
           ../../../lib/swarm/src/SwarmRosShowCase.cpp \
           ../../../lib/encoding/src/AES.cpp \
           ../../../lib/encoding/src/ECC.cpp \
           ../../../lib/encoding/src/CRC.cpp \
           ../../../lib/encoding/src/RSA.cpp \
           ../../../lib/encoding/src/hash.cpp \
           ../../../lib/FUTS/src/uintTest.cpp \
           ../../../lib/DBI/src/DBIStorage.cpp \
           ../../../lib/DBI/src/DBISync.cpp \
           ../../../lib/swarm/src/SwarmAvoidance.cpp \
           ../../../lib/swarm/src/SwarmSpaceStatus.cpp \
           ../../../lib/src/Angle.cpp \
           ../../../lib/encoding/src/random.cpp \
           ../../../lib/math/src/prime.cpp \
           ../../../lib/DBI/src/fdhs.cpp \
           ../../../lib/DBI/src/DBIClauseManager.cpp \
           ../../../lib/FOS/src/flist.cpp
HEADERS  += uidev.h \
            ../../../lib/FOS/inc/buffer.h \
            ../../../lib/RCOS/inc/rc.h \
            ../../../lib/RCOS/inc/rcGraph.h \
            ../../../lib/RCOS/inc/rcHardDriver.h \
            ../../../lib/RCOS/inc/rcType.h \
            ../../../lib/swarm/inc/SwarmType.h \
            ../../../lib/inc/DJICommonType.h \
            ../../../lib/TASTS/inc/TASTS.h \
            ../../../lib/DBI/inc/DBIStorage.h \
            ../../../lib/DBI/inc/DBIType.h \
            ../../../lib/DBI/inc/DBIShadow.h \
            ../../../lib/DBI/inc/DBISync.h \
            ../../../lib/DBI/inc/DBIPipeline.h \
            ../../../lib/swarm/inc/SwarmSensor.h \
            ../../../lib/swarm/inc/SwarmAvoidance.h \
            ../../../lib/FUTS/inc/FUTS.h \
            ../../../lib/FUTS/inc/VICON.h \
            ../../../lib/swarm/inc/Swarm.h \
            ../../../lib/encoding/inc/AES.h \
            ../../../lib/encoding/inc/ECC.h \
            ../../../lib/encoding/inc/CRC.h \
            ../../../lib/encoding/inc/RSA.h \
            ../../../lib/encoding/inc/hash.h \
            ../../../lib/FUTS/inc/unitTest.h \
            ../../../lib/FUTS/inc/FUTSType.h \
            ../../../lib/FOS/inc/Flist.h \
            ../../../lib/swarm/inc/SwarmSpaceStatus.h \
            ../../../lib/TASTS/inc/FlightSimulator.h \
            ../../../lib/SSM/inc/SSM.h \
            ../../../lib/encoding/inc/random.h \
            ../../../lib/math/inc/prime.h \
            ../../../lib/DBI/inc/DBIClauseManager.h \
            ../../../lib/DBI/inc/DBI.h \
            ../../../lib/DBI/inc/fdhs.h \
            ../../../lib/DBI/inc/fdhs_link.h \
            ../../../lib/DBI/inc/fdhs_type.h \
            ../../../lib/DBI/inc/fmu_type.h \
            ../../../lib/dev/dev.h \
            ../../../lib/dev/devtype.h
INCLUDEPATH += \
            ../../../lib/DBI/inc \
            ../../../lib/encoding/inc \
            ../../../lib/FOS/inc \
            ../../../lib/FUTS/inc \
            ../../../lib/gridmap/inc \
            ../../../lib/RCOS/inc \
            ../../../lib/swarm/inc \
            ../../../lib/math/inc \
            ../../../lib/dev \
            ../../../lib/swarm/simulator/inc
FORMS +=  uidev.ui
DJILIB += RCSDK\
          #GRIDMAP\
          TASTS
}

message("DJILIB:"$$DJILIB)

contains(DEPENDENCE,DJILIB){
contains(DJILIB, GROUNDSTATION){
message("Please check your QT has installed webenigne package")
QT +=  webenginewidgets
DEFINES += GROUNDSTATION
}

contains(DJILIB, GRIDMAP){
message("using OpenGL for gridmap.")
QT += opengl
DEFINES += OPENGL

GRIDMAP_INC += \
            ../../../lib/gridmap/inc/gridmap.h \
            ../../../lib/gridmap/inc/gridmapKernel.h

GRIDMAP_SRC += \
            ../../../lib/gridmap/src/gridmapKernel.cpp \
            ../../../lib/gridmap/src/gridmap.cpp

SOURCES += $$GRIDMAP_SRC
HEADERS += $$GRIDMAP_INC
}

contains(DJILIB,ONBOARDSDK){
include( ../../../platform/qt/QonboardSDK.pri))
#include( ../../../osdk-core/osdk-core.pri)
include( ../../../test/test-core/test-base.pri)
include(DataPannel.pri)
include(ControlPannel.pri)
}
}




FORMS    += djionboardsdk.ui \
    autotest.ui \
    qwaypoints.ui \
    mfiopannel.ui \
    recorder.ui

RESOURCES +=

DISTFILES += \
    CMakeLists.txt \
    DataPannel.pri \
    ControlPannel.pri


message("finish compile")
