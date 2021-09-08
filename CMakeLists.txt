cmake_minimum_required(VERSION 3.16)
project(Inn)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
include_directories(.)

add_executable(${PROJECT_NAME} main.cpp
        server/logger/logger.cpp server/logger/logger.h
        server/service/user/user.cpp server/service/user/user.h
        server/server.cpp server/server.h
        server/conn/conn.cpp server/conn/conn.h
        server/thread/thread.h server/thread/locker.h
        server/controller/sql.cpp server/controller/sql.h
        server/service/auth/auth.cpp server/service/auth/auth.h
        server/controller/router.cpp server/controller/router.h
        server/service/chat/chatting_room.cpp server/service/chat/chatting_room.h
        server/constant/log_define.h server/test.cpp server/model/define.h)

target_link_libraries(${PROJECT_NAME} libmysqlclient.so)