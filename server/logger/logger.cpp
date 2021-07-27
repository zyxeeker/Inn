//
// Created by ZYXeeker on 2021/4/6.
//

#include "logger.h"
#include <iostream>

std::string Logger::toString(LogLevel level) {
    switch (level) {
#define TRANS(level) \
    case LogLevel::level: \
        return #level; \
        break;

        TRANS(DEBUG);
        TRANS(INFO);
        TRANS(WARN);
        TRANS(ERROR);
        TRANS(FATAL);
        TRANS(UNKNOWN);
#undef TRANS
        default:
            return "UNKNOWN";
    }
    return "UNKNOWN";
}

Logger::Logger(LogLevel level, std::string content) {
    char date_t[50];

    time_t now = time(nullptr);

    strftime(date_t, 50, "%x %X", localtime(&now));
    std::cout << date_t << " [" << toString(level) << "]" << ":" << content << std::endl;
}

void Logger::Out(LogLevel level, std::string content) {
    auto *log = new Logger(level, content);
}