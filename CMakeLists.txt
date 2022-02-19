cmake_minimum_required(VERSION 3.13)

project(mayaQtMouseEvent)

find_package(Qt5 REQUIRED COMPONENTS Widgets Core)
find_package(Maya REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB MQTWE_SOURCES src/*.cpp)
add_library(mayaQtWidgetEvent SHARED ${MQTWE_SOURCES})
target_compile_definitions(mayaQtMouseEvent PUBLIC LINUX)
target_include_directories(
    mayaQtMouseEvent PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(
    mayaQtMouseEvent PRIVATE
        Maya::Foundation
        Maya::OpenMaya
        Maya::OpenMayaUI
        Qt5::Widgets
        Qt5::Core
)

install(TARGETS mayaQtMouseEvent DESTINATION plugins)
