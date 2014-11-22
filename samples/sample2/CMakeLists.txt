cmake_minimum_required(VERSION 2.8)
project(sample2)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${CMAKE_PROJECT_NAME})