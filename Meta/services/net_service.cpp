//
// Created by zyxeeker on 11/19/21.
//

#include "net_service.h"
#include <fcntl.h>
#include "Meta/util/conf.h"

Meta::NetService *Meta::NetService::service_ = nullptr;
ssl_ctx_st *Meta::NetService::m_ctx = nullptr;
ssl_st *Meta::NetService::m_ssl = nullptr;

int Meta::NetService::CreateSocket() {
    // socket
    if ((m_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        return -1;
    return 0;
}

int Meta::NetService::BindSocket() const {
    struct sockaddr_in p_address{};
    // IPv4
    p_address.sin_family = AF_INET;
    // Port
    p_address.sin_port = htons(GET_META_CONF->port);
    p_address.sin_addr.s_addr = INADDR_ANY;
    if (bind(m_fd, (struct sockaddr *) &p_address, sizeof(p_address)) == -1)
        return -1;
    return 0;
}

int Meta::NetService::SetListen() const {
    // max num of connections
    if (listen(m_fd, GET_META_CONF->listen_num) == -1)
        return -1;
    return 0;
}

int Meta::NetService::SetSocketNonBlocking() const {
    return fcntl(m_fd, F_SETFL, O_NONBLOCK);
}

int Meta::NetService::InitEpoll() {
    // create fd of epoll
    if ((m_epoll_fd = epoll_create1(0)) == -1)
        return m_epoll_fd;
    m_event.events = EPOLLIN | EPOLLET;
    m_event.data.fd = m_fd;
    // add fd to let epoll watch
    epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, m_fd, &m_event);
    return 0;
}

void Meta::NetService::Run() {
    auto *events = new epoll_event[GET_META_CONF->event_num];
    int p_cur_events_num, p_fd, conn_fd, len;
    char buff[4096];
    while (m_runSt) {
        p_cur_events_num = epoll_wait(m_epoll_fd, events, 50, -1);
        for (int i = 0; i < p_cur_events_num; ++i) {
            // add new connection
            p_fd = events[i].data.fd;
            if (p_fd == m_fd) {
                conn_fd = accept(m_fd, (struct sockaddr *) &m_client_address, &m_client_address_length);
                ModEpoll(conn_fd, EPOLLIN | EPOLLET, EPOLL_CTL_ADD);
            }
                // already connected to progress data
            else if (events[i].events & EPOLLIN) {
                len = recv(p_fd, buff, BUFSIZ, 0);
                if (len <= 0)
                    continue;
                buff[len] = '\0';
                LOG_D(buff);
            }
                // send data when have data need to send
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
//    SSL_set_fd(m_ssl, m_fd);
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

void Meta::NetService::ModEpoll(int fd, int events, int op) {
    struct epoll_event event{};
    event.data.fd = fd;
    event.events = events;
    epoll_ctl(m_epoll_fd, op, fd, &event);
}