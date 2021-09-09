//
// Created by ZYXeeker on 2021/4/6.
//

#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include "conn.h"

namespace Inn {
    int ConnPool::m_epollFd;

    bool ConnPool::InitEpoll() {
        // epoll 初始化构建
        m_epollFd = epoll_create1(0);

        m_event.events = EPOLLIN | EPOLLET;
        m_event.data.fd = m_listenFd;

        // 将事件加入 epoll 事件列表
        epoll_ctl(m_epollFd, EPOLL_CTL_ADD, m_listenFd, &m_event);

        LOG("epoll init successful");

    }

    void ConnPool::EpollMod(int sock_fd, int statue, int way) {
        struct epoll_event event;
        event.data.fd = sock_fd;
        event.events = statue;
        epoll_ctl(m_epollFd, way, sock_fd, &event);
    }

    void ConnPool::SocketSend(std::string message, int socket_fd) {
        send(socket_fd, message.c_str(), message.size(), 0);
        close(socket_fd);
    }

    bool ConnPool::Init() {
        struct sockaddr_in addr;
        int on = 1;

        m_router = new Router[m_MAX_EVENTS];

        // socket
        if ((m_listenFd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
            LOGE("Socket init fail");

        // bind
        addr.sin_family = AF_INET;
        addr.sin_port = htons(m_port);
        addr.sin_addr.s_addr = INADDR_ANY;

        //// socket参数
        // 允许端口复用
        setsockopt(m_listenFd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

        if (bind(m_listenFd, (struct sockaddr *) &addr, sizeof(addr)) == -1)
            LOGE("Bind init fail");

        // listen
        if (listen(m_listenFd, 5) == -1)
            LOGE("Listen init fail");

        LOG("Socket init successful");

        InitEpoll();
    }

    void ConnPool::StartListen() {
        epoll_event *events = new epoll_event[m_MAX_EVENTS];
        while (m_listenSt) {
            int CUR_EVENTS_NUMS = epoll_wait(m_epollFd, events, m_MAX_EVENTS, -1);

            for (int i = 0; i < CUR_EVENTS_NUMS; ++i) {
                // 新连接加入epoll
                int sock_fd = events[i].data.fd;
                if (sock_fd == m_listenFd) {
                    int conn_fd = accept(m_listenFd, (struct sockaddr *) &m_clientAddr, &m_clientAddrLen);
                    EpollMod(conn_fd, EPOLLIN | EPOLLET, EPOLL_CTL_ADD);
                }
                    // 已连接用户并读取数据
                else if (events[i].events & EPOLLIN) {
                    char buff[4096];
                    int len = recv(sock_fd, buff, BUFSIZ, 0);
                    if (len <= 0)
                        continue;
                    buff[len] = '\0';

                    std::string test_str1 = buff;

                    m_router[i].SetDstData(sock_fd, test_str1);
                    m_routerPool->append_work(m_router + i);
#if SO_DEBUG
                    LOGD(test_str1);
#endif
                }
                    // 已连接用户存在有数据待发送
                else if (events[i].events & EPOLLOUT) {
                    std::string message = m_router->m_message;
                    std::cout << message << std::endl;
                    send(sock_fd, message.c_str(), message.size(), 0);
                    EpollMod(sock_fd, EPOLLIN | EPOLLET);
//                    close(sock_fd);
                }
            }
        }
    }

}