//
// Created by zyxeeker on 11/18/21.
//

#ifndef INN_DEFINE_H
#define INN_DEFINE_H

enum LOG_LEVEL {
    UNKNOWN,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL
};

enum NET_INIT_ST {
    INIT_SUCCESS,
    CREATE_FAILED,
    BIND_FAILED,
    LISTEN_FAILED,
    EPOLL_FAILED
};

#endif //INN_DEFINE_H
