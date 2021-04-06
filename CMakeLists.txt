cmake_minimum_required(VERSION 3.16)
project(Inn)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(${PROJECT_NAME} main.cpp server/logger/logger.cpp server/logger/logger.h server/logger_test.cpp)
