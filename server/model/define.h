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

#endif //INN_DEFINE_H
