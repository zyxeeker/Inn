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
#include "../thread/thread.h"
#include "../controller/auth.h"
#include "../controller/router.h"

class Router;

namespace conn_pool {
    class conns {
    public:
        conns(thread_pool<Router> *router_pool, int port, int MAX_EVENTS, int BUFF_SIZE) :
                m_router_pool(router_pool), m_port(port), m_MAX_EVENTS(MAX_EVENTS) {
            Log::logger(Log::log_level::level::INFO, "Server is working at " + std::to_string(port));
        }

        bool init();

        bool init_epoll();

        void conn_listen();

        static void epoll_mod(int epoll_fd, int sock_fd, int statue, int way = EPOLL_CTL_MOD);

        static void sock_send(std::string message, int sock_fd);

    private:
        int m_port;
        int m_epoll_fd;
        int m_listen_fd;

        int m_MAX_EVENTS;

        struct sockaddr_in m_clientAddr;
        struct epoll_event m_event;

        socklen_t m_clientAddrLen = sizeof(m_clientAddr);
        // 监听状态
        bool m_listen_status{true};

        Router *m_router;

        thread_pool<Router> *m_router_pool;

    };
}
#endif //INN_CONN_H
