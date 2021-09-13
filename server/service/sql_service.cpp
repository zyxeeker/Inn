//
// Created by ZYXeeker on 2021/4/9.
//

#include "sql_service.h"
#include "server/logger/logger.h"

namespace Inn {
//    int conn_pool::m_MAX_CONN_NUMBER = 0;
//    int conn_pool::m_CUR_CONN_NUMBER = 0;

    bool SQLConnPool::CreateConn() {
        MYSQL *conn = mysql_init(nullptr);
        std::string database = "testdb";
        conn = mysql_real_connect(conn,
                                  m_host.c_str(), m_user.c_str(),
                                  m_pwd.c_str(), database.c_str(), m_port,
                                  nullptr, 0);
        if (!conn)
            return false;
        m_SQL_pool.push_back(conn);
        return true;
    }


    bool SQLConnPool::Init() {
        MYSQL *conn;
        for (int i = 0; i < m_MAX_CONN_NUMBER; ++i) {
            if (!CreateConn()) {
                LOGE("MYSQL`S CONNECTION CREATED FAIL!");
                break;
            }
        }
        LOG("MYSQL`S CONNECTION CREATED!");
        return true;

    }


    MYSQL * SQLConnPool::GetAvailConn() {
        if (m_CUR_CONN_NUMBER <= m_MAX_CONN_NUMBER) {
            MYSQL *conn = nullptr;
            conn = m_SQL_pool.front();
            m_SQL_pool.pop_front();
            ++m_CUR_CONN_NUMBER;
            return conn;
        }
        LOGF("MYSQL`S CONNECTION NUMBER ALREADY TO MAX!");
        return nullptr;
    }

    bool SQLConnPool::ReleaseConn(MYSQL *conn) {
        if (m_CUR_CONN_NUMBER < 0)
            return false;
        LOG("RELEASE A CONNECTION!");

        mysql_close(conn);
        --m_CUR_CONN_NUMBER;

        // 释放后添加新的连接
        if (CreateConn()) {
            LOG("ADD A NEW CONNECTION!");
            return true;
        } else {
            LOGE("A NEW CONNECTION FAILED TO ADD!");
            return false;
        }
    }
}