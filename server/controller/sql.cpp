//
// Created by ZYXeeker on 2021/4/9.
//

#include "sql.h"
#include "../logger/logger.h"

namespace SQL {
    bool conn_pool::create_conn() {
        MYSQL conn;
        mysql_init(&conn);
        std::string database = "chat_users";
        MYSQL *statue = mysql_real_connect(&conn, m_host.c_str(), m_user.c_str(), m_pwd.c_str(), database.c_str(),
                                           m_port,
                                           nullptr, 0);
        if (!statue)
            return false;
        m_SQL_pool.push_back(&conn);
        return true;
    }


    bool conn_pool::init() {
        MYSQL *conn;
        for (int i = 0; i < m_MAX_CONN_NUMBER; ++i) {
            if (create_conn())
                Log::logger(Log::log_level::level::INFO, "MYSQL`S CONNECTION CREATED!");
            else
                Log::logger(Log::log_level::level::ERROR, "MYSQL`S CONNECTION CREATED FAIL!");
        }
        return true;
    }

    MYSQL *conn_pool::get_avail_conn() {
        if (m_CUR_CONN_NUMBER <= m_MAX_CONN_NUMBER) {
            MYSQL *conn;
            conn = m_SQL_pool.front();
            m_SQL_pool.pop_front();
            ++m_CUR_CONN_NUMBER;
            return conn;
        }
        Log::logger(Log::log_level::level::FATAL, "MYSQL`S CONNECTION NUMBER ALREADY TO MAX!");
        return nullptr;
    }

    bool conn_pool::release_conn(MYSQL *conn) {
        if (m_CUR_CONN_NUMBER < 0)
            return false;

        mysql_close(conn);
        --m_CUR_CONN_NUMBER;

        // 释放后添加新的连接
        if (create_conn()) {
            Log::logger(Log::log_level::level::INFO, "ADD A NEW CONNECTION!");
            return true;
        } else {
            Log::logger(Log::log_level::level::ERROR, "A NEW CONNECTION FAILED TO ADD!");
            return false;
        }
    }
}