cmake_minimum_required(VERSION 2.8)

project(tlelib)

set(TLELIB_SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(TLELIB_INC_DIR ${CMAKE_SOURCE_DIR}/include)

set(TLELIB_SOURCES
${TLELIB_SRC_DIR}/func.cpp
${TLELIB_SRC_DIR}/node.cpp
${TLELIB_SRC_DIR}/stream.cpp
${TLELIB_SRC_DIR}/dataset.cpp
)

include_directories(${TLELIB_INC_DIR})
add_library(${PROJECT_NAME} STATIC ${TLELIB_SOURCES})
