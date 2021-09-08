//
// Created by ZYXeeker on 2021/4/6.
//

#ifndef INN_LOGGER_H
#define INN_LOGGER_H

#include <string>
#include <ctime>
#include "server/model/define.h"

class Logger {
public:
    std::string toString(LOG_LEVEL level);

    Logger(LOG_LEVEL level, std::string content);

public:
    static void Out(LOG_LEVEL level, std::string content);

};

#endif //INN_LOGGER_H
