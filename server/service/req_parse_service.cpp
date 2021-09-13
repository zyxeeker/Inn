//
// Created by z on 9/13/21.
//

#include "req_parse_service.h"

namespace Inn{
    int ReqParseService::Core(std::string &str) {
        if (!str.find("LOGIN", 0))
            return INN_USER_LOGIN;
        if (!str.find("REG", 0))
            return INN_USER_REG;
        if (!str.find("CHAT", 0))
            return INN_USER_CHAT;
    }
}
