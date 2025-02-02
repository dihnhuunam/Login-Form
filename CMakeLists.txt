cmake_minimum_required(VERSION 3.5)

project(Login-Form LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11) 

list(APPEND CMAKE_PREFIX_PATH "/home/dihnhuunam/Qt5.13.2/5.13.2/gcc_64/lib/cmake/Qt5")
find_package(Qt5 COMPONENTS Widgets REQUIRED)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(INC_DIR "${CMAKE_SOURCE_DIR}/Includes")
set(SRC_DIR "${CMAKE_SOURCE_DIR}/Sources")
set(QRC "${CMAKE_SOURCE_DIR}/Resources.qrc")

# Define source and header files
file(GLOB SOURCES ${SRC_DIR}/*.cpp)
file(GLOB HEADERS ${INC_DIR}/*.h)

# Add library
add_library(Login-Form-Libs SHARED ${SOURCES} ${HEADERS} ${QRC})
target_include_directories(Login-Form-Libs PUBLIC ${INC_DIR})
target_link_libraries(Login-Form-Libs PUBLIC Qt5::Widgets)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE Login-Form-Libs)

# Installing
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION Bin
)
install(TARGETS Login-Form-Libs
    LIBRARY DESTINATION Libs
    ARCHIVE DESTINATION Libs
)
install(DIRECTORY 
    ${CMAKE_CURRENT_SOURCE_DIR}/Includes/
    DESTINATION Includes
)
install(FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/README.md
    DESTINATION Share
)

# CPack configuration
set(CPACK_PACKAGE_DESCRIPTION "Login Form ")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_VENDOR "Dinh Huu Nam")
set(CPACK_PACKAGE_CONTACT "dihnhuunam@gmail.com")
set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}")
set(CPACK_GENERATOR "ZIP")
include(CPack)
