cmake_minimum_required(VERSION 2.8)
include(FRCDeploy)

project(RER-2014)
find_package(WPILib)

file(GLOB_RECURSE SOURCE_CODE *.cpp)

include_directories(
    ${WPILib_INCLUDE_DIRS}
)

#add_custom_target(envr COMMAND " bash export WIND_BASE=/usr/powerpc-wrs-vxworks/wind_base")

add_executable(robot_module ${SOURCE_CODE})
target_link_libraries(robot_module ${WPILib_LIBRARY})

#add_dependencies(robot_module envr)

add_make_deploy(robot_module 10.34.99.2)
