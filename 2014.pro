TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += RERRobot.h \
    generated.h \
    tcpconnection.h \
    solenoidbreakout.h \
    action.h \
    buttonreg.h

SOURCES += RERRobot.cpp \
    tcpconnection.cpp \
    solenoidbreakout.cpp \
    action.cpp \
    buttonreg.cpp

OTHER_FILES += \
    sample.txt \
    CMakeLists.txt \
    .gitignore

INCLUDEPATH += /usr/powerpc-wrs-vxworks/include/WPILib
