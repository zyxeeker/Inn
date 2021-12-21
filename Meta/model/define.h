//
// Created by zyxeeker on 11/18/21.
//

#ifndef INN_DEFINE_H
#define INN_DEFINE_H

#include <cstdint>

typedef struct server_config_ {
    uint16_t port = 9006;
    uint16_t event_num = 20;
    uint16_t listen_num = 5;
} server_config;

#endif //INN_DEFINE_H
