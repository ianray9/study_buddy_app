cmake_minimum_required(VERSION 3.10)
project(StudyBuddyApp CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING
        "Choose the type of build (debug or release)" FORCE)
endif()

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

include_directories(include)

file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/data")

if(CMAKE_BUILD_TYPE STREQUAL "debug")
    set(EXECUTABLE_NAME app_debug)
else()
    set(EXECUTABLE_NAME app)
endif()

add_executable(${EXECUTABLE_NAME} ${SOURCES})
