//
// Created by ZYXeeker on 2021/4/6.
//

#ifndef INN_LOGGER_H
#define INN_LOGGER_H

#include <string>
#include <ctime>
#include "server/constant/log_define.h"

class Logger {
public:
    std::string toString(LogLevel level);

    Logger(LogLevel level, std::string content);

public:
    static void Out(LogLevel level, std::string content);

};

#endif //INN_LOGGER_H
