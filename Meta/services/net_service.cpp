//
// Created by zyxeeker on 11/19/21.
//

#include "net_service.h"

#if 1
#define PORT 9006
#endif

Meta::NetService *Meta::NetService::m_s = nullptr;
ssl_ctx_st *Meta::NetService::m_ctx = nullptr;
ssl_st *Meta::NetService::m_ssl = nullptr;
int Meta::NetService::m_epollFd = 0;
int Meta::NetService::m_listenFd = 0;

NET_INIT_ST Meta::NetService::SocketInit() {
    struct sockaddr_in p_address{};
    int on = 1;
    /// socket
    if ((m_listenFd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        return CREATE_FAILED;
    /// socket参数
    // 允许端口复用
    setsockopt(m_listenFd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    /// bind
    p_address.sin_family = AF_INET;
    p_address.sin_port = htons(PORT);
    p_address.sin_addr.s_addr = INADDR_ANY;
    if (bind(m_listenFd, (struct sockaddr *) &p_address, sizeof(p_address)) == -1)
        return BIND_FAILED;
    /// listen
    if (listen(m_listenFd, 5) == -1)
        return LISTEN_FAILED;
    // epoll 初始化构建
    try {
        m_epollFd = epoll_create1(0);
        m_event.events = EPOLLIN | EPOLLET;
        m_event.data.fd = m_listenFd;
        // 将事件加入 epoll 事件列表
        epoll_ctl(m_epollFd, EPOLL_CTL_ADD, m_listenFd, &m_event);
    } catch (const char *msg) {
        LOG_F(__FUNCTION__, msg);
        return EPOLL_FAILED;
    }
    return INIT_SUCCESS;
}

void Meta::NetService::Run() {
    auto *events = new epoll_event[50];
    while (m_runSt) {
        int CUR_EVENTS_NUMS = epoll_wait(m_epollFd, events, 50, -1);
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
                LOG_D(__FUNCTION__, buff);
            }
                // 已连接用户存在有数据待发送
            else if (events[i].events & EPOLLOUT) {
//                send(sock_fd, message.c_str(), message.size(), 0);
//                EpollMod(sock_fd, EPOLLIN | EPOLLET);
//                    close(sock_fd);
            }
        }
    }
}

void Meta::NetService::SslInit() {
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();
}

void Meta::NetService::SslCreteCtx() {
    m_ctx = SSL_CTX_new(TLS_server_method());
//    TODO:Set Buffer
    SSL_CTX_set_ex_data(m_ctx, 0, nullptr);
//    TODO:Options
    SSL_CTX_set_options(m_ctx, 0);
}

void Meta::NetService::SslCreateConnection() {
    m_ssl = SSL_new(m_ctx);
    SSL_set_fd(m_ssl, m_listenFd);
    SSL_set_accept_state(m_ssl);
}

void Meta::NetService::SslHandShake() {
    SSL_do_handshake(m_ssl);
    SSL_get_error(m_ssl, 0);
}

void Meta::NetService::SslShutDown() {
    SSL_shutdown(m_ssl);
//    TODO:SSL_SESSION
    SSL_CTX_remove_session(m_ctx, nullptr);
    SSL_get_session(m_ssl);
    SSL_free(m_ssl);
}

void Meta::NetService::close() {

}

void Meta::NetService::EpollMod(int socketFd, int statue, int way) {
    struct epoll_event event;
    event.data.fd = socketFd;
    event.events = statue;
    epoll_ctl(m_epollFd, way, socketFd, &event);
}