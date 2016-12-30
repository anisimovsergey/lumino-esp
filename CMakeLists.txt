cmake_minimum_required (VERSION 2.6)
project(Moikot)

set (CMAKE_CXX_FLAGS "-fno-rtti -fno-exceptions -std=c++11 -Isrc -Wall")
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.hpp")

set(CMAKE_MACOSX_RPATH 1)
add_library(moikot SHARED ${SOURCES})
