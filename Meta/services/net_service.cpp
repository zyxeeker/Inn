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
int Meta::NetService::m_fd = 0;

void Meta::NetService::SocketInit() {
    struct sockaddr_in p_address;
    int on = 1;

    // socket
    if ((m_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        LOG_D(__FUNCTION__, "Socket init fail");

    // bind
    p_address.sin_family = AF_INET;
    p_address.sin_port = htons(PORT);
    p_address.sin_addr.s_addr = INADDR_ANY;

    //// socket参数
    // 允许端口复用
    setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    if (bind(m_fd, (struct sockaddr *) &p_address, sizeof(p_address)) == -1)
        LOG_D(__FUNCTION__, "Bind init fail");

    // listen
    if (listen(m_fd, 5) == -1)
        LOG_D(__FUNCTION__, "Listen init fail");

    LOG_D(__FUNCTION__, "Socket init successful");

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
    SSL_set_fd(m_ssl, m_fd);
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