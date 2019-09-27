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
set(CMAKE_CXX_STANDARD 17)

# Using deprecated codecvt header until a suitable replacement for its
# capability is available - see GitHub issue #9
add_definitions(-D_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING)

find_package (Threads)

# Using conan for dependencies
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# The test executable
file (GLOB TEST_SRC test/*.cpp)
add_executable(test-qlib ${TEST_SRC})
target_link_libraries(test-qlib PRIVATE
    ${CONAN_LIBS}
    ${CMAKE_THREAD_LIBS_INIT}
)
