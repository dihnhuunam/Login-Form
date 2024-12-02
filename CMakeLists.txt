cmake_minimum_required(VERSION 3.5)

project(Login-Form LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11) 

list(APPEND CMAKE_PREFIX_PATH "/home/dihnhuunam/Qt5.13.2/5.13.2/gcc_64/lib/cmake/Qt5")
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Define source and header files
set(PROJECT_SOURCES
    Sources/main.cpp
    Sources/mainwindow.cpp
    Includes/mainwindow.h
    Resources.qrc 
)

# Add executable
add_executable(${CMAKE_PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt5::Widgets)

# Include directories
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Includes
)

# Install targets
install(TARGETS ${CMAKE_PROJECT_NAME}
    RUNTIME DESTINATION bin
)

# Install documentation 
install(FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/README.md
    ${CMAKE_CURRENT_SOURCE_DIR}/License.txt
    DESTINATION share/${CMAKE_PROJECT_NAME}/doc
)

# CPack configuration
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_NAME "Login-Form")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Login-Form built using CMake")
set(CPACK_PACKAGE_VENDOR "Dinh Huu Nam")
set(CPACK_PACKAGE_CONTACT "dihnhuunam@example.com")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_GENERATOR "DEB;TGZ")
set(CPACK_SOURCE_GENERATOR "TGZ")

# Include CPack to enable packaging
include(CPack)
