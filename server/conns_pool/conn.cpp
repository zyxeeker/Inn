//
// Created by ZYXeeker on 2021/4/6.
//

#include <netinet/in.h>
#include <cstring>
#include "conn.h"

namespace conn_pool {
    bool conns::init() {
        struct sockaddr_in addr;
        int on = 1;

        // socket
        if ((m_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
            Log::logger(Log::log_level::level::ERROR, "Socket init fail");

        // bind
        addr.sin_family = AF_INET;
        addr.sin_port = htons(m_port);
        addr.sin_addr.s_addr = INADDR_ANY;

        //// socket参数
        // 允许端口复用
        setsockopt(m_socket_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

        if (bind(m_socket_fd, (struct sockaddr *) &addr, sizeof(addr)) == -1)
            Log::logger(Log::log_level::level::ERROR, "Bind init fail");

        // listen
        if (listen(m_socket_fd, 5) == -1)
            Log::logger(Log::log_level::level::ERROR, "Listen init fail");

        Log::logger(Log::log_level::level::INFO, "Socket init successful");
    }

    void conns::conn_listen() {
        //发送欢迎信息
        while (true) {
            int m_conn = accept(m_socket_fd, (struct sockaddr *) &m_clientAddr, &m_clientAddrLen);
            int len = send(m_conn, "Welcome to my server/n", 21, 0);
            char buff[1024];
            /*接收客户端的数据并将其发送给客户端--recv返回接收到的字节数，send返回发送的字节数*/
            while ((len = recv(m_conn, buff, BUFSIZ, 0)) > 0) {
                buff[len] = '\0';
                std::string test_str1 = buff;
                Log::logger(Log::log_level::level::DEBUG, test_str1);
                if (send(m_conn, buff, len, 0) < 0) {
                    Log::logger(Log::log_level::level::ERROR, "Write error!");
                }
            }
        }
    }
}