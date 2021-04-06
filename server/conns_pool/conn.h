//
// Created by ZYXeeker on 2021/4/6.
//

#ifndef INN_CONN_H
#define INN_CONN_H

#include "sys/socket.h"
#include "../logger/logger.h"
#include <iostream>
#include <string>

namespace conn_pool {
    class conns {
    public:
        conns(int port) : m_port(port) {
            Log::logger(Log::log_level::level::INFO, "Server is working at " + std::to_string(port));
        }

        void conn_listen();

    private:
        int m_port;
//        int
        bool m_listen_status;
    };
}
#endif //INN_CONN_H
