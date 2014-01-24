TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += RERRobot.h

SOURCES += RERRobot.cpp \
    init.cpp \
    test.cpp \
    autonomous.cpp \
    teleop.cpp \
    disabled.cpp

OTHER_FILES += \
    PPC603gnu/compile.sh
