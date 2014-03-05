TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += RERRobot.h \
    action.h \
    arduino.h \
    const.h \
    drivesys.h \
    generated.h \
        input/jsbase.h \
        input/operator.h \
    jaglog.h \
    modeautonomous.h \
    modebase.h \
    modedisabled.h \
    modeteleoperated.h \
    modetest.h \
    outputcommon.h \
    solenoidbreakout.h \
    tcpconnection.h \

SOURCES += RERRobot.cpp \
    action.cpp \
    drivesys.cpp \
        input/jsbase.h \
        input/operator.h \
    jaglog.cpp \
    modeautonomous.cpp \
    modebase.cpp \
    modedisabled.cpp \
    modeteleoperated.cpp \
    modetest.cpp \
    outputcommon.cpp \
    solenoidbreakout.cpp \
    tcpconnection.cpp \

OTHER_FILES += \
    sample.txt \
    CMakeLists.txt \
    .gitignore

INCLUDEPATH += /usr/powerpc-wrs-vxworks/include/WPILib
