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

include(CPack)

set(CPACK_PACKAGE_NAME "Login-Form")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION "A Basic Login Form.")
set(CPACK_PACKAGE_VENDOR "DinhHuuNam")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_GENERATOR "ZIP;DEB")

install(TARGETS Login-Form
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)