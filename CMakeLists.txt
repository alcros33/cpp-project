cmake_minimum_required(VERSION 3.12)

project(QTExample)
set(MAIN_APP_NAME "Main")
set(MAIN_LIBRARY_NAME "engine")

enable_language(C CXX)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# --------------------------------------------------------------------------------
#                          Cmake Basic Config
# --------------------------------------------------------------------------------

# Set version number (change as needed). These definitions are available
# by including "exampleConfig.h" in the source. 
# See exampleConfig.h.in for some more details.
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)

#Include stuff. No change needed.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
include(ConfigSafeGuards)
include(Colors)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)


# --------------------------------------------------------------------------------
#                          Include packages, libraries, etc.
# --------------------------------------------------------------------------------

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)
# Create code from a list of Qt designer ui files.
set(CMAKE_AUTOUIC ON) # use this if you have CMake 3.x instead of the following

# --------------------------------------------------------------------------------
#                          Set binary output dir
# --------------------------------------------------------------------------------
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    SET(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/bin")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

# --------------------------------------------------------------------------------
#                          Compile flags (change as needed).
# --------------------------------------------------------------------------------
# Set the C++ standard you wish to use (will apply to all files).
# If you do not use any features that limits the standard required,
# you could omit this line.

set(CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


# Things to always include as flags. Change as needed.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra -Wno-sign-compare -Wno-unused-parameter")  

# Build-type specific flags. Change as needed.
SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -Wl,-subsystem,windows")
SET(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

message(STATUS "Building with the following extra flags: ${CMAKE_CXX_FLAGS}")
# --------------------------------------------------------------------------------
#                         Locate files (no change needed).
# --------------------------------------------------------------------------------

# We make sure that CMake sees all the files.
include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/utils
    ${PROJECT_SOURCE_DIR}/tests
    ${PROJECT_SOURCE_DIR}/external/googletest
    ${PROJECT_SOURCE_DIR}/external/googletest/include)

# Make variables referring to all the sources and test files.
file(GLOB SOURCES "src/*.cpp")
file(GLOB TESTFILES "tests/*.cpp")
file(GLOB APPFILES "app/*.cpp")
set(TEST_MAIN unit_tests)  # Default name for test executable (change if you wish).

# --------------------------------------------------------------------------------
#                            Build! (Change as needed)
# --------------------------------------------------------------------------------

# Compile all sources into a library. Called engine here (change if you wish).
add_library(${MAIN_LIBRARY_NAME} SHARED ${SOURCES} )

# Add an executable for the file main.cpp, here called main.x.
# If you add more executables, copy these three lines accordingly.

add_executable(${MAIN_APP_NAME} ${APPFILES})   # Name of exec. and location of file.
add_dependencies(${MAIN_APP_NAME} ${MAIN_LIBRARY_NAME})     
target_link_libraries(${MAIN_APP_NAME} ${MAIN_LIBRARY_NAME} Qt5::Widgets) 

# Deploy QT on Windows
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_custom_command(
        TARGET Main
        POST_BUILD
        COMMAND windeployqt --release $<TARGET_FILE:${MAIN_APP_NAME}>)
endif()

# --------------------------------------------------------------------------------
#                         Make Tests (no change needed).
# --------------------------------------------------------------------------------

# Add a make target 'gtest', that runs the tests (and builds all dependencies).
# The setup of Google Test is done at the very end of this file.
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_executable(${TEST_MAIN} ${TESTFILES})
    add_dependencies(${TEST_MAIN} googletest ${MAIN_LIBRARY_NAME})
    target_link_libraries(${TEST_MAIN} googletest ${MAIN_LIBRARY_NAME} pthread)
    add_custom_target(gtest 
        COMMAND "${PROJECT_BINARY_DIR}/${TEST_MAIN}"
        DEPENDS ${MAIN_LIBRARY_NAME} ${TEST_MAIN})

    # Add a standard make target 'test' that runs the tests under CTest (only as an alt. to gtest).
    include(CTest)
    enable_testing()
    add_test(unit_tests ${PROJECT_BINARY_DIR}/${TEST_MAIN})
endif()

# --------------------------------------------------------------------------------
#                         Google Test (no change needed).
# --------------------------------------------------------------------------------

# The following makes sure that an up-to-date version of googletest is available,
# and built so that it may be used by your tests. 
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_custom_target( git_update
        COMMAND git submodule init
        COMMAND git submodule update
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} )
    add_library( googletest
        ${PROJECT_SOURCE_DIR}/external/googletest/src/gtest-all.cc
        ${PROJECT_SOURCE_DIR}/external/googletest/src/gtest_main.cc )
    add_dependencies(googletest git_update)
    set_source_files_properties(${PROJECT_SOURCE_DIR}/external/googletest/src/gtest-all.cc  PROPERTIES GENERATED 1)
    set_source_files_properties(${PROJECT_SOURCE_DIR}/external/googletest/src/gtest_main.cc PROPERTIES GENERATED 1)
endif()

# --------------------------------------------------------------------------------
#                            Misc (no change needed).
# --------------------------------------------------------------------------------
# Have CMake parse the config file, generating the config header, with
# correct definitions. Here only used to make version number available to
# the source code. Include "exampleConfig.h" (no .in suffix) in the source.
configure_file (
  "${PROJECT_SOURCE_DIR}/include/Config.h.in"
  "${PROJECT_BINARY_DIR}/Config.h")
# add the binary tree to the search path for include files
# so that we will find exampleConfig.h
include_directories("${PROJECT_BINARY_DIR}")

# Ask CMake to output a compile_commands.json file for use with things like Vim YCM.
set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )
