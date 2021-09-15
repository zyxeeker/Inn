//
// Created by ZYXeeker on 2021/4/10.
//

#ifndef INN_ROUTER_SERVICE_H
#define INN_ROUTER_SERVICE_H

#include <stdlib.h>
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
        void DoLoginReq();
        void DoRegReq();
        void DoChatReq();
        void DoHeartBeatReq();
        void DoLogoutReq();
        std::string GetMsg() const;

    private:
        std::string m_message;
        std::string m_text;
        int m_socketFd;
        MYSQL *m_conn;
    };
};

#endif //INN_ROUTER_SERVICE_H
