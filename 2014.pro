TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += RERRobot.h \
    generated.h \
    solenoidbreakout.h \
    input/jsbase.h \
    arduino.h \
    const.h \
    drivesys.h \
    jaglog.h \
    modeautonomous.h \
    modebase.h \
    modedisabled.h \
    modeteleoperated.h \
    modetest.h \
    outputcommon.h \
    ports.h \
    input/operator.h

SOURCES += RERRobot.cpp \
    solenoidbreakout.cpp \
    input/jsbase.cpp \
    drivesys.cpp \
    jaglog.cpp \
    modeautonomous.cpp \
    modebase.cpp \
    modedisabled.cpp \
    modeteleoperated.cpp \
    modetest.cpp \
    outputcommon.cpp \
    input/operator.cpp

OTHER_FILES += \
    sample.txt \
    CMakeLists.txt \
    .gitignore \
    README.md

INCLUDEPATH += /usr/powerpc-wrs-vxworks/include/WPILib
