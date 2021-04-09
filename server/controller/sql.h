//
// Created by ZYXeeker on 2021/4/9.
//

#ifndef INN_SQL_H
#define INN_SQL_H

#include <string>
#include "mysql/mysql.h"
#include <list>

namespace SQL {
    class conn_pool {
    public:
        conn_pool(std::string host, std::string user, std::string pwd, int max_conn_number, int port = 3306) :
                m_host(host), m_user(user), m_pwd(pwd), m_MAX_CONN_NUMBER(max_conn_number), m_port(port) {};

        // 创建连接
        bool create_conn();

        // 连接池初始化
        bool init();

        // 从连接池中返回一个有效链接
        MYSQL *get_avail_conn();

        // 释放已经使用的连接
        bool release_conn(MYSQL *conn);

    private:
        // 最大连接数
        int m_MAX_CONN_NUMBER;
        // 当前连接数
        int m_CUR_CONN_NUMBER{0};
        // 数据库连接池
        std::list<MYSQL *> m_SQL_pool;

        // 数据库登陆数据
        int m_port;
        std::string m_host;
        std::string m_user;
        std::string m_pwd;
    };

}
#endif //INN_SQL_H
