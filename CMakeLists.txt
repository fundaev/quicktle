cmake_minimum_required(VERSION 2.8)

project(quicktle)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(TLELIB_SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(TLELIB_INC_DIR ${CMAKE_SOURCE_DIR}/include)
set(TLELIB_SAMPLES_DIR ${CMAKE_SOURCE_DIR}/samples)
set(TLELIB_TESTS_DIR ${CMAKE_SOURCE_DIR}/test)

set(TLELIB_SOURCES
${TLELIB_SRC_DIR}/func.cpp
${TLELIB_SRC_DIR}/node.cpp
${TLELIB_SRC_DIR}/stream.cpp
${TLELIB_SRC_DIR}/dataset.cpp
)

include_directories(${TLELIB_INC_DIR})

option(BUILD_SAMPLES "Build samples" ON)
if (BUILD_SAMPLES)
	add_subdirectory(${TLELIB_SAMPLES_DIR}/sample1)
	add_subdirectory(${TLELIB_SAMPLES_DIR}/sample2)
	add_subdirectory(${TLELIB_SAMPLES_DIR}/sample3)
endif (BUILD_SAMPLES)

option(BUILD_TESTS "Build tests" ON)
if (BUILD_TESTS)
	add_subdirectory(${TLELIB_TESTS_DIR})
endif(BUILD_TESTS)

add_library(${PROJECT_NAME} SHARED ${TLELIB_SOURCES})
