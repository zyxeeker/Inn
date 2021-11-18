cmake_minimum_required(VERSION 3.16)
project(Inn)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
include_directories(.)

#add_executable(${PROJECT_NAME} main.cpp
#        server/logger/logger.cpp server/logger/logger.h
#        server/service/user_service.cpp server/service/user_service.h
#        server/server.cpp server/server.h
#        server/conn/conn.cpp server/conn/conn.h
#        server/thread/thread.h server/thread/locker.h
#        server/service/sql_service.cpp server/service/sql_service.h
#        server/service/auth_service.cpp server/service/auth_service.h
#        server/service/router_service.cpp server/service/router_service.h
#        server/service/chatting_room_service.cpp server/service/chatting_room_service.h
#        server/test.cpp server/model/define.h server/service/req_parse_service.cpp server/service/req_parse_service.h)

add_executable(${PROJECT_NAME} server/test.cpp
        Meta/tools/logger.cpp Meta/tools/logger.h Meta/model/define.h)

target_link_libraries(${PROJECT_NAME} libmysqlclient.so)