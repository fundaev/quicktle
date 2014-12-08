cmake_minimum_required(VERSION 2.8)

project(quicktle)
set(VERSION "2.0.0")

if (UNIX)
set(CMAKE_INSTALL_PREFIX "/usr")
endif(UNIX)

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
set(TLELIB_HEADERS
${TLELIB_INC_DIR}/func.h
${TLELIB_INC_DIR}/node.h
${TLELIB_INC_DIR}/stream.h
${TLELIB_INC_DIR}/dataset.h
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

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib COMPONENT bin)
install(FILES ${TLELIB_HEADERS} DESTINATION include/quicktle COMPONENT hdr)
install(FILES ${TLELIB_SOURCES} DESTINATION src/quicktle COMPONENT src)

#if (UNIX)
#	execute_process(COMMAND dpkg --print-architecture OUTPUT_VARIABLE ARTITECTURE)
#endif (UNIX)


set(CPACK_GENERATOR "TGZ;DEB;RPM")
set(CPACK_PROJECT_CONFIG_FILE ${CMAKE_SOURCE_DIR}/CPackConfig.cmake)
set(CPACK_PACKAGE_VERSION ${VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Provides C++ library for operations with TLE-files")
set(CPACK_PACKAGE_FILE_NAME ${CMAKE_PROJECT_NAME}-${CPACK_PACKAGE_VERSION})
include(CPack)