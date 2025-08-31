cmake_minimum_required(VERSION 3.10)
project(StudyBuddyApp CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set default build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING
        "Choose the type of build (debug or release)" FORCE)
endif()

# Gather all source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Include header files
include_directories(include)

# Ensure the data directory exists
file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/data")

# Output executable in project root
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Set executable name based on build type
if(CMAKE_BUILD_TYPE STREQUAL "debug")
    set(EXECUTABLE_NAME app_debug)
else()
    set(EXECUTABLE_NAME StudyBuddyApp)
endif()

# Define the executable
add_executable(${EXECUTABLE_NAME} ${SOURCES})
