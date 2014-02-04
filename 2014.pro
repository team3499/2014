TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += RERRobot.h \
    generated.h

SOURCES += RERRobot.cpp \
    init.cpp \
    test.cpp \
    autonomous.cpp \
    teleop.cpp \
    disabled.cpp

OTHER_FILES += \
    sample.txt \
    CMakeLists.txt \
    .gitignore

INCLUDEPATH += /usr/powerpc-wrs-vxworks/include/WPILib
