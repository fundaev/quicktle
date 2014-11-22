cmake_minimum_required(VERSION 2.8)

project(testquicktle)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${CMAKE_PROJECT_NAME} ${GTEST_LIBRARIES} pthread)
add_test(AllTests test)