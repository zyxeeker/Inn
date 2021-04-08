cmake_minimum_required(VERSION 3.16)
project(Inn)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(${PROJECT_NAME} server/logger/logger.cpp server/logger/logger.h server/user/user.cpp server/user/user.h server/test.cpp server/test.cpp server/server.cpp server/server.h server/conns_pool/conn.cpp server/conns_pool/conn.h server/thread/thread_pool.h server/thread/locker.h)
