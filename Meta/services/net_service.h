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
#include <sys/epoll.h>
#include "Meta/model/define.h"

#if 1
#include "Meta/tools/logger.h"
#endif

namespace Meta {
    class NetService {
    public:
        static NetService *Instance() {
            if (!service_)
                service_ = new NetService;
            return service_;
        }
        int CreateSocket();
        int BindSocket() const;
        int SetListen() const;
        int SetSocketNonBlocking() const;
        int InitEpoll();

        void Run();
        static void SslInit();
        static void SslCreteCtx();
        static void SslHandShake();
        static void SslCreateConnection();
        static void SslShutDown();
        static void close();
    private:
        void ModEpoll(int fd, int events, int op);
    private:
        bool m_runSt = true;
        static NetService *service_;
        static ssl_ctx_st *m_ctx;
        static ssl_st *m_ssl;
        int m_epoll_fd;
        int m_fd = -1;

        struct sockaddr_in m_client_address;
        struct epoll_event m_event;
        socklen_t m_client_address_length = sizeof(sockaddr_in);
    };
}

#endif //INN_NET_SERVICE_H
