cmake_minimum_required(VERSION 3.5)

project(Login-Form LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11) 

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
    Sources/main.cpp
    Sources/mainwindow.cpp
    Includes/mainwindow.h
    Resources.qrc 
)

add_executable(Login-Form ${PROJECT_SOURCES})

target_link_libraries(Login-Form PRIVATE Qt5::Widgets)

target_include_directories(Login-Form PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Includes
    ${CMAKE_CURRENT_SOURCE_DIR}/Forms
)
