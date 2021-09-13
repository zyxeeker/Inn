//
// Created by ZYXeeker on 2021/4/9.
//

#ifndef INN_SQL_SERVICE_H
#define INN_SQL_SERVICE_H

#include <string>
#include "mysql/mysql.h"
#include <list>
#include <iostream>

namespace Inn {
    class SQLConnPool {
    public:
        SQLConnPool(std::string host, std::string user, std::string pwd, int max_conn_number, int port = 3306) :
                m_MAX_CONN_NUMBER(max_conn_number), m_CUR_CONN_NUMBER(0), m_host(host), m_user(user), m_pwd(pwd),
                m_port(port) {};

        // 创建连接
        bool CreateConn();

        // 连接池初始化
        bool Init();

        // 从连接池中返回一个有效链接
        MYSQL *GetAvailConn();

        // 释放已经使用的连接
        bool ReleaseConn(MYSQL *conn);

//        // 最大连接数
//        static int m_MAX_CONN_NUMBER;
//        // 当前连接数
//        static int m_CUR_CONN_NUMBER;

    private:
        // 最大连接数
        const int m_MAX_CONN_NUMBER;
        // 当前连接数
        int m_CUR_CONN_NUMBER;
        // 数据库连接池
        std::list<MYSQL *> m_SQL_pool;

        // 数据库登陆数据
        const int m_port;
        const std::string m_host;
        const std::string m_user;
        const std::string m_pwd;
    };

}
#endif //INN_SQL_SERVICE_H
