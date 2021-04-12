//
// Created by ZYXeeker on 2021/4/10.
//

#include "chatting_room.h"

int u2u::send(const std::string &receiver) {
    int sock_fd = user::user_socket[receiver];
    conn_pool::conns::epoll_mod(sock_fd, EPOLLOUT | EPOLLET);
    return 0;
}