cmake_minimum_required(VERSION 3.5)

project(Login-Form LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11) 

list(APPEND CMAKE_PREFIX_PATH "/home/dihnhuunam/Qt5.13.2/5.13.2/gcc_64/lib/cmake/Qt5")
find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
    Sources/main.cpp
    Sources/mainwindow.cpp
    Includes/mainwindow.h
    Resources.qrc 
)

add_executable(${CMAKE_PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt5::Widgets)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Includes
)