//
// Created by ZYXeeker on 2021/4/10.
//

#ifndef INN_CHATTING_ROOM_H
#define INN_CHATTING_ROOM_H

#include "server/service/user/user.h"
#include "server/conn/conn.h"

class Chat {

};

class u2u : private Chat {
public:
    static int send(const std::string &receiver);
};

class u2a : private Chat {

};

#endif //INN_CHATTING_ROOM_H
