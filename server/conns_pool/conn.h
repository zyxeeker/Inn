//
// Created by ZYXeeker on 2021/4/6.
//

#ifndef INN_CONN_H
#define INN_CONN_H

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../logger/logger.h"
#include <iostream>
#include <string>
#include <sys/epoll.h>

namespace conn_pool {
    class conns {
    public:
        conns(int port, int MAX_EVENTS, int BUFF_SIZE) : m_port(port), m_MAX_EVENTS(MAX_EVENTS),
                                                         m_BUFF_SIZE(BUFF_SIZE) {
            Log::logger(Log::log_level::level::INFO, "Server is working at " + std::to_string(port));
        }

        bool init();

        bool init_epoll();

        void conn_listen();

    private:
        int m_port;
        int m_epoll_fd;
        int m_listen_fd;


        char *m_BUFF;

        int m_BUFF_SIZE;
        int m_MAX_EVENTS;
        int m_CUR_EVENTS;

        struct sockaddr_in m_clientAddr;
        struct epoll_event m_event;

        socklen_t m_clientAddrLen = sizeof(m_clientAddr);
        // 监听状态
        bool m_listen_status{true};
    };
}
#endif //INN_CONN_H
