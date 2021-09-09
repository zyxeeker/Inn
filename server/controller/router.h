//
// Created by ZYXeeker on 2021/4/10.
//

#ifndef INN_ROUTER_H
#define INN_ROUTER_H

#include "sql.h"
#include "server/service/auth/auth.h"
#include "server/conn/conn.h"
#include "server/service/user/user.h"
#include "server/service/chat/chatting_room.h"

namespace Inn{
    class Router {
    public:
        void SetDstData(int socketFd, std::string text);

        void DoReq(MYSQL *conn);

        std::string m_message;
    private:
        std::string m_text;

        int m_socketFd;

    };
};

#endif //INN_ROUTER_H
