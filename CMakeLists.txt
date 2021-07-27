cmake_minimum_required(VERSION 3.16)
project(Inn)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
include_directories(.)

add_executable(${PROJECT_NAME} main.cpp
        server/logger/logger.cpp server/logger/logger.h
        server/model/user/user.cpp server/model/user/user.h
        server/server.cpp server/server.h
        server/conn/conn.cpp server/conn/conn.h
        server/thread/thread.h server/thread/locker.h
        server/controller/sql.cpp server/controller/sql.h
        server/model/auth/auth.cpp server/model/auth/auth.h
        server/controller/router.cpp server/controller/router.h
        server/model/chat/chatting_room.cpp server/model/chat/chatting_room.h
        server/constant/log_define.h)

#target_link_libraries(${PROJECT_NAME} libmysqlclient.so)