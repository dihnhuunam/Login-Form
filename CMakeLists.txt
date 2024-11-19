cmake_minimum_required(VERSION 3.5)

project(Login-Form LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/Forms)

set(PROJECT_SOURCES
    Sources/main.cpp
    Sources/mainwindow.cpp
    Includes/mainwindow.h
    Forms/mainwindow.ui
)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Resources.qrc)
    set(PROJECT_SOURCES ${PROJECT_SOURCES} Resources.qrc)
endif()

add_executable(Login-Form ${PROJECT_SOURCES})

target_link_libraries(Login-Form PRIVATE Qt5::Widgets)

target_include_directories(Login-Form 
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/Includes
    ${CMAKE_CURRENT_SOURCE_DIR}/Forms
)
