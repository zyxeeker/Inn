//
// Created by ZYXeeker on 2021/4/10.
//

#ifndef INN_ROUTER_H
#define INN_ROUTER_H

#include "sql.h"
#include "auth.h"

class Router {
public:
    Router(SQL::conn_pool *sql_pool) : m_sql_pool(sql_pool) {};

    virtual void parse_operations() = 0;

    virtual void sql_operations() = 0;

private:
    SQL::conn_pool *m_sql_pool;

};

class Auth : private Router {
public:
    void parse_operations() override;

    void sql_operations() override;

private:
    auth m_auth;
};

class Chat : private Router {
public:
    void parse_operations() override;

    void sql_operations() override;

private:
};

#endif //INN_ROUTER_H
