//
// Created by zyxeeker on 11/18/21.
//

#ifndef INN_DEFINE_H
#define INN_DEFINE_H

#include <cstdint>

typedef struct server_config_ {
    uint16_t port;
    uint16_t event_num;
    uint16_t listen_num;
} server_config;

#endif //INN_DEFINE_H
