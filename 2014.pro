TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += RERRobot.h \
    generated.h

SOURCES += RERRobot.cpp

OTHER_FILES += \
    sample.txt \
    CMakeLists.txt \
    .gitignore

INCLUDEPATH += /usr/powerpc-wrs-vxworks/include/WPILib
