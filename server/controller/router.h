//
// Created by ZYXeeker on 2021/4/10.
//

#ifndef INN_ROUTER_H
#define INN_ROUTER_H

#include "sql.h"
#include "server/model/auth/auth.h"
#include "server/conn/conn.h"
#include "server/model/user/user.h"
#include "server/model/chat/chatting_room.h"

class Router {
public:
    void init(int sock_fd, std::string text);

    void do_req(MYSQL *conn);

    std::string m_message;
private:
    std::string m_text;

    int m_sock_fd;

};

#endif //INN_ROUTER_H
