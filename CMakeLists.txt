# Top-level Cmake project file for building qLib tests
#
# Note that qLib is a header-only library, so does not need to be built to
# be used.
#
# Copyright Igor Siemienowicz 2018
# Distributed under the Boost Software License, Version 1.0. (See
# accompanying file LICENSE_1_0.txt or copy at
# https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.10)
project(qLib LANGUAGES CXX)
# set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD 14)

find_package (Threads)

# set(CMAKE_MODULE_PATH .)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

# --- Boost Info ---
# message("Boost:")
# message("    root     : ${CONAN_BOOST_ROOT}")
# message("    includes : ${CONAN_INCLUDE_DIRS_BOOST}")
# message("    libs     : ${CONAN_LIB_DIRS_BOOST}")

add_definitions(${CONAN_DEFINES_BOOST})

include_directories(
    .
    third-party
    third-party/fmt/include
    ${CONAN_INCLUDE_DIRS_BOOST}
)

link_directories(${CONAN_LIB_DIRS_BOOST})

add_subdirectory(third-party/fmt EXCLUDE_FROM_ALL)

# The test executable
file (GLOB TEST_SRC test/*.cpp)
add_executable(test-qlib ${TEST_SRC})
target_link_libraries(test-qlib PRIVATE
    ${CONAN_LIBS_BOOST}
    fmt-header-only
    ${CMAKE_THREAD_LIBS_INIT}
)
