cmake_minimum_required(VERSION 3.0.0)

# Use C++14
set(CMAKE_CXX_STANDARD 14)

# Enable debug symbols by default
# Must be done before project() statement
# Can also set it on the command line: -DCMAKE_BUILD_TYPE=Release)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

project(CYBORG)

set(EXECUTABLE_NAME "CYBORG")

message("CYBORG Project - By Tonzo Studios")
message(STATUS "System info: ${CMAKE_SYSTEM_NAME} ${CMAKE_HOST_SYSTEM_PROCESSOR}")

# Set version information in a version.h file
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
configure_file(
    "${PROJECT_SOURCE_DIR}/version.h.in"
    "${PROJECT_BINARY_DIR}/version.h"
)
include_directories("${PROJECT_BINARY_DIR}")

# TODO: Add specifics for other operating systems
if(NOT BIN_PREFIX)
    set(BIN_PREFIX ${CMAKE_INSTALL_PREFIX}/bin)
endif()

file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB HEADERS ${CMAKE_SOURCE_DIR}/src/*.h)

# Add lazarus library
add_subdirectory(${CMAKE_SOURCE_DIR}/lazarus)
include_directories(${CMAKE_SOURCE_DIR}/lazarus/src)

# Executable definition
add_executable(${EXECUTABLE_NAME}
    ${SOURCES}
    ${HEADERS}
)

# Link lazarus library
add_dependencies(${EXECUTABLE_NAME} lazarus)
target_link_libraries(${EXECUTABLE_NAME} ${CMAKE_BINARY_DIR}/lazarus/liblazarus.so)
target_include_directories(${EXECUTABLE_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/lazarus/src/lazarus)

# Build types (Debug or Release)
if(CMAKE_BUILD_TYPE STREQUAL Debug)
    message(STATUS "Build type set to Debug")
    set(CMAKE_VERBOSE_MAKEFILE ON)
else()
    message(STATUS "Build type set to Release")
    message(STATUS "Installation directory: ${BIN_PREFIX}")
    install(TARGETS ${EXECUTABLE_NAME} DESTINATION ${BIN_PREFIX})
endif()
