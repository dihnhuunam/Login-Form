cmake_minimum_required(VERSION 3.5)

project(Login-Form LANGUAGES CXX VERSION 1.0.0)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11) 

list(APPEND CMAKE_PREFIX_PATH "/home/dihnhuunam/Qt5.13.2/5.13.2/gcc_64/lib/cmake/Qt5")
find_package(Qt5 COMPONENTS Widgets REQUIRED)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Define source and header files
set(PROJECT_SOURCES
    Sources/mainwindow.cpp
    Includes/mainwindow.h
    Resources.qrc 
)

# Add executable
add_library(mainLib SHARED ${PROJECT_SOURCES})
target_link_libraries(mainLib PUBLIC Qt5::Widgets)

add_executable(${CMAKE_PROJECT_NAME} Sources/main.cpp)
target_link_libraries( ${CMAKE_PROJECT_NAME} PUBLIC mainLib)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Includes
)

# Install targets
install(TARGETS ${CMAKE_PROJECT_NAME}
    RUNTIME DESTINATION bin
)

install(TARGETS mainLib
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(DIRECTORY Includes DESTINATION include)

install(FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/README.md
    ${CMAKE_CURRENT_SOURCE_DIR}/License.txt
    DESTINATION share
)

# CPack configuration
set(CPACK_PACKAGE_DESCRIPTION "Just CPacke example")
set(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${VERSION_PATCH}")
set(CPACK_PACKAGE_VENDOR "Dinh Huu Nam")
set(CPACK_PACKAGE_CONTACT "dihnhuunam@example.com")
set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
set(CPACK_GENERATOR "ZIP")
include(CPack)
