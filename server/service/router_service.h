//
// Created by ZYXeeker on 2021/4/10.
//

#ifndef INN_ROUTER_SERVICE_H
#define INN_ROUTER_SERVICE_H

#include "sql_service.h"
#include "auth_service.h"
#include "server/conn/conn.h"
#include "user_service.h"
#include "chatting_room_service.h"
#include "req_parse_service.h"

namespace Inn{
    class Router {
    public:
        void SetDstData(int socketFd, std::string text);
        void StartService(MYSQL *conn);
        void DoLoginReq(MYSQL *conn);
        void DoRegReq(MYSQL *conn);
        void DoChatReq();

        std::string m_message;
    private:
        std::string m_text;
        int m_socketFd;

    };
};

#endif //INN_ROUTER_SERVICE_H
