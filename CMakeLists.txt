cmake_minimum_required(VERSION 3.16)
project(Inn)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
include_directories(.)

add_executable(${PROJECT_NAME} server/test.cpp server/logger/logger.cpp server/logger/logger.h server/user/user.cpp server/user/user.h server/server.cpp server/server.h server/conn/conn.cpp server/conn/conn.h server/thread/thread.h server/thread/locker.h server/controller/sql.cpp server/controller/sql.h server/controller/auth.cpp server/controller/auth.h client/client_connct.cpp)

target_link_libraries(${PROJECT_NAME} libmysqlclient.so)