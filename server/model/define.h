//
// Created by z on 9/8/21.
//

#ifndef INN_DEFINE_H
#define INN_DEFINE_H

enum LOG_LEVEL{
    UNKNOWN,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL
};

enum AUTH_LOGIN_RESULT{
    LOGIN_NOT_EXISTED,
    LOGIN_ERROR,
    LOGIN_FAIL,
    LOGIN_SUC,
    LOGIN_REPEAT,
};

enum AUTH_REG_RESULT{
    REG_ERROR,
    REG_FAIL,
    REG_SUC
};

enum REQ_OP{
    INN_USER_LOGIN,
    INN_USER_REG,
    INN_USER_CHAT
};

enum REQ_RESULT{
    INN_USER_LOGIN_SUC = 0,
    INN_USER_LOGIN_WRONG = 1,
    INN_USER_REG_SUC = 2,
    INN_USER_REG_WRONG = 3
};

#endif //INN_DEFINE_H
