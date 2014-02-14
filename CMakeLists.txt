# Rivers Edge Robotics (Team 3499) 2014 Robot Code
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(RER_2014)

INCLUDE(FRCDeploy)
FIND_PACKAGE(WPILib)

SET(RER_2014_HEADERS ### =================== HEADERS =================== ###
    RERRobot.h
    generated.h
#    tcpconnection.h
    solenoidbreakout.h
    action.h
<<<<<<< HEAD
#    input/buttonreg.h
#    input/jsbase.h
=======
    input/buttonreg.h
    input/jsbase.h
>>>>>>> 8b2bb403687039d61902eb0ffa909933d8031d12
)

SET(RER_2014_SOURCES ### =================== SOURCES =================== ###
    RERRobot.cpp
#    tcpconnection.cpp
    solenoidbreakout.cpp
    action.cpp
<<<<<<< HEAD
#    input/buttonreg.cpp
#    input/jsbase.cpp
=======
    input/buttonreg.cpp
    input/jsbase.cpp
>>>>>>> 8b2bb403687039d61902eb0ffa909933d8031d12
)

### =================== CONFIG =================== ###

INCLUDE_DIRECTORIES(
    ${CMAKE_BINARY_DIR}
    ${WPILib_INCLUDE_DIRS}
)

# Generate build date
EXECUTE_PROCESS(COMMAND date "+%D %T" OUTPUT_VARIABLE G_MAKE_BUILD_TIME)
STRING(STRIP ${G_MAKE_BUILD_TIME} G_MAKE_BUILD_TIME)
CONFIGURE_FILE(generated.h gen_out.h @ONLY)

MESSAGE(STATUS "Building Rivers Edge Robotics (Team 3499) 2014 Robot Code")
MESSAGE(STATUS "Build Time: ${G_MAKE_BUILD_TIME}")
MESSAGE(STATUS "Toolchain: ${CMAKE_TOOLCHAIN_FILE}")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unused-parameter -Wno-ignored-qualifiers -ansi -std=c++11")

### =================== BUILD =================== ###

ADD_DEFINITIONS(-DBUILDING)

# Add target for robot code
ADD_EXECUTABLE(robot_module ${RER_2014_SOURCES})
TARGET_LINK_LIBRARIES(robot_module ${WPILib_LIBRARY})

# Add deploy target
ADD_MAKE_DEPLOY(robot_module 10.34.99.2)