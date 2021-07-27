//
// Created by ZYXeeker on 2021/4/6.
//

#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include "conn.h"

namespace conn_pool {
    int conns::m_epoll_fd;

    bool conns::init_epoll() {
        // epoll 初始化构建
        m_epoll_fd = epoll_create1(0);

        m_event.events = EPOLLIN | EPOLLET;
        m_event.data.fd = m_listen_fd;

        // 将事件加入 epoll 事件列表
        epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, m_listen_fd, &m_event);

        Logger::Out(INFO, "epoll init successful");

    }

    void conns::epoll_mod(int sock_fd, int statue, int way) {
        struct epoll_event event;
        event.data.fd = sock_fd;
        event.events = statue;
        epoll_ctl(m_epoll_fd, way, sock_fd, &event);
    }

    void conns::sock_send(std::string message, int sock_fd) {
        send(sock_fd, message.c_str(), message.size(), 0);
        close(sock_fd);
    }

    bool conns::init() {
        struct sockaddr_in addr;
        int on = 1;

        m_router = new Router[m_MAX_EVENTS];

        // socket
        if ((m_listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
            Logger::Out(ERROR, "Socket init fail");

        // bind
        addr.sin_family = AF_INET;
        addr.sin_port = htons(m_port);
        addr.sin_addr.s_addr = INADDR_ANY;

        //// socket参数
        // 允许端口复用
        setsockopt(m_listen_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

        if (bind(m_listen_fd, (struct sockaddr *) &addr, sizeof(addr)) == -1)
            Logger::Out(ERROR, "Bind init fail");

        // listen
        if (listen(m_listen_fd, 5) == -1)
            Logger::Out(ERROR, "Listen init fail");

        Logger::Out(INFO, "Socket init successful");

        init_epoll();
    }

    void conns::conn_listen() {
        epoll_event *events = new epoll_event[m_MAX_EVENTS];
        while (m_listen_status) {
            int CUR_EVENTS_NUMS = epoll_wait(m_epoll_fd, events, m_MAX_EVENTS, -1);

            for (int i = 0; i < CUR_EVENTS_NUMS; ++i) {
                // 新连接加入epoll
                int sock_fd = events[i].data.fd;
                if (sock_fd == m_listen_fd) {
                    int conn_fd = accept(m_listen_fd, (struct sockaddr *) &m_clientAddr, &m_clientAddrLen);
                    epoll_mod(conn_fd, EPOLLIN | EPOLLET, EPOLL_CTL_ADD);
                }
                    // 已连接用户并读取数据
                else if (events[i].events & EPOLLIN) {
                    char buff[4096];
                    int len = recv(sock_fd, buff, BUFSIZ, 0);
                    if (len <= 0)
                        continue;
                    buff[len] = '\0';

                    std::string test_str1 = buff;

                    m_router[i].init(sock_fd, test_str1);
                    m_router_pool->append_work(m_router + i);

                    Logger::Out(DEBUG, test_str1);
                }
                    // 已连接用户存在有数据待发送
                else if (events[i].events & EPOLLOUT) {
                    std::string message = m_router->m_message;
                    std::cout << message << std::endl;
                    send(sock_fd, message.c_str(), message.size(), 0);
                    epoll_mod(sock_fd, EPOLLIN | EPOLLET);
//                    close(sock_fd);
                }
            }
        }
    }

}