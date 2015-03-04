cmake_minimum_required(VERSION 2.8)

project(quicktle)
set(VERSION "2.0.0")

if (UNIX)
set(CMAKE_INSTALL_PREFIX "/usr")
endif(UNIX)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(QUICKTLE_SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(QUICKTLE_INC_DIR ${CMAKE_SOURCE_DIR}/include)
set(QUICKTLE_SAMPLES_DIR ${CMAKE_SOURCE_DIR}/samples)
set(QUICKTLE_TESTS_DIR ${CMAKE_SOURCE_DIR}/test)

set(QUICKTLE_SOURCES
${QUICKTLE_SRC_DIR}/func.cpp
${QUICKTLE_SRC_DIR}/node.cpp
${QUICKTLE_SRC_DIR}/stream.cpp
${QUICKTLE_SRC_DIR}/dataset.cpp
)
set(QUICKTLE_HEADERS
${QUICKTLE_INC_DIR}/quicktle/func.h
${QUICKTLE_INC_DIR}/quicktle/node.h
${QUICKTLE_INC_DIR}/quicktle/stream.h
${QUICKTLE_INC_DIR}/quicktle/dataset.h
)


include_directories(${QUICKTLE_INC_DIR})

option(BUILD_SAMPLES "Build samples" ON)
if (BUILD_SAMPLES)
	add_subdirectory(${QUICKTLE_SAMPLES_DIR}/sample1)
	add_subdirectory(${QUICKTLE_SAMPLES_DIR}/sample2)
	add_subdirectory(${QUICKTLE_SAMPLES_DIR}/sample3)
endif (BUILD_SAMPLES)

option(BUILD_TESTS "Build tests" ON)
if (BUILD_TESTS)
	add_subdirectory(${QUICKTLE_TESTS_DIR})
endif(BUILD_TESTS)

add_library(${PROJECT_NAME} SHARED ${QUICKTLE_SOURCES})

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib COMPONENT bin)
install(FILES ${QUICKTLE_HEADERS} DESTINATION include/quicktle COMPONENT hdr)
install(FILES ${QUICKTLE_SOURCES} DESTINATION src/quicktle COMPONENT src)

#if (UNIX)
#	execute_process(COMMAND dpkg --print-architecture OUTPUT_VARIABLE ARTITECTURE)
#endif (UNIX)


set(CPACK_GENERATOR "TGZ;DEB;RPM")
set(CPACK_PROJECT_CONFIG_FILE ${CMAKE_SOURCE_DIR}/CPackConfig.cmake)
set(CPACK_PACKAGE_VERSION ${VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Provides C++ library for operations with TLE-files")
set(CPACK_PACKAGE_FILE_NAME ${CMAKE_PROJECT_NAME}-${CPACK_PACKAGE_VERSION})
include(CPack)