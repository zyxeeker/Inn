//
// Created by zyxeeker on 11/19/21.
//

#ifndef INN_NET_SERVICE_H
#define INN_NET_SERVICE_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>

#if 1
#include "Meta/tools/logger.h"
#endif

namespace Meta {
    class NetService {
    public:
        static NetService *Instance() {
            if (!m_s)
                m_s = new NetService;
            return m_s;
        }
        static void SocketInit();
        static void SslInit();
        static void SslCreteCtx();
        static void SslHandShake();
        static void SslCreateConnection();
        static void SslShutDown();
        static void close();
    private:

    private:
        static NetService *m_s;
        static ssl_ctx_st *m_ctx;
        static ssl_st *m_ssl;
        static int m_fd;
    };
}

#endif //INN_NET_SERVICE_H
