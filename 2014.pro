TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += RERRobot.h \
    generated.h \
    tcpconnection.h \
    solenoidbreakout.h \
    action.h \
    input/buttonreg.h \
    input/jsbase.h

SOURCES += RERRobot.cpp \
    tcpconnection.cpp \
    solenoidbreakout.cpp \
    action.cpp \
    input/buttonreg.cpp \
    input/jsbase.cpp

OTHER_FILES += \
    sample.txt \
    CMakeLists.txt \
    .gitignore

INCLUDEPATH += /usr/powerpc-wrs-vxworks/include/WPILib
