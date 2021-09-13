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
#include <iostream>
#include <string>
#include <sys/epoll.h>
#include "server/logger/logger.h"
#include "server/thread/thread.h"
#include "server/service/auth_service.h"
#include "server/service/router_service.h"

class Router;

namespace Inn {
    class ConnPool {
    public:
        ConnPool(thread_pool<Router> *router_pool, int port, int MAX_EVENTS, int BUFF_SIZE) :
                m_routerPool(router_pool), m_port(port), m_MAX_EVENTS(MAX_EVENTS) {
            LOG("Server is working at " + std::to_string(port));
        }

        bool Init();

        bool InitEpoll();

        void StartListen();

        static void EpollMod(int sock_fd, int statue, int way = EPOLL_CTL_MOD);

        static void SocketSend(std::string message, int sock_fd);

    public:
        static int m_epollFd;

    private:
        int m_port;
        int m_listenFd;

        int m_MAX_EVENTS;

        struct sockaddr_in m_clientAddr;
        struct epoll_event m_event;

        socklen_t m_clientAddrLen = sizeof(m_clientAddr);
        // 监听状态
        bool m_listenSt{true};

        Router *m_router;

        thread_pool<Router> *m_routerPool;

    };
}
#endif //INN_CONN_H
