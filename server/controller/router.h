//
// Created by ZYXeeker on 2021/4/10.
//

#ifndef INN_ROUTER_H
#define INN_ROUTER_H

#include "sql.h"
#include "auth.h"
#include "../conn/conn.h"
#include "../user/user.h"
#include "chatting_room.h"

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
