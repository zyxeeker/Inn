//
// Created by ZYXeeker on 2021/4/6.
//

#ifndef INN_LOGGER_H
#define INN_LOGGER_H

#include <string>
#include <ctime>
#include "server/model/define.h"

#define LOGD(x) Logger(DEBUG,x);
#define LOG(x) Logger(INFO,x);
#define LOGW(x) Logger(WARN,x);
#define LOGE(x) Logger(ERROR,x);
#define LOGF(x) Logger(FATAL,x);
#define LOGU(x) Logger(UNKNOW,x);

class Logger {
public:
    std::string toString(LOG_LEVEL level);

    Logger(LOG_LEVEL level, std::string content);

};



#endif //INN_LOGGER_H
