cmake_minimum_required(VERSION 2.6)
PROJECT(ocmath)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OCMATH_BINARY_DIR}")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/packages/")

include_directories(src)

#timer library
find_package(OCTIMER REQUIRED)
include_directories(${OCTIMER_INCLUDE_DIR})

add_definitions(-DOC_SIMD)

if (WIN32)
add_definitions(-DOC_WIN32)
else()
add_definitions(-W -Wall -ansi -pedantic -ggdb -O3)
endif()
#release mode
#add_definitions(-DRELEASE)

add_subdirectory(src)
add_subdirectory(test)
