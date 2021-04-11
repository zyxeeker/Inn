//
// Created by ZYXeeker on 2021/4/10.
//

#ifndef INN_ROUTER_H
#define INN_ROUTER_H

#include "sql.h"
#include "auth.h"
#include "../conn/conn.h"

class Router {
public:
//    Router(SQL::conn_pool *sql_pool) : m_sql_pool(sql_pool) {};
    void init(int epoll_fd, int sock_fd, std::string text);

    void test(MYSQL *conn);

    static std::string m_message;
private:
    std::string m_text;
    Auth m_auth;

    int m_epoll_fd;
    int m_sock_fd;

};



#endif //INN_ROUTER_H
