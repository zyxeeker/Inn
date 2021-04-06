//
// Created by ZYXeeker on 2021/4/6.
//

#include "logger.h"
#include <iostream>

namespace Log {
    std::string Log::log_level::toString(log_level::level level) {
        switch (level) {
#define TRANS(level) \
                case (log_level::level): \
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

    Log::logger::logger(log_level::level level, std::string content) {
        char date_t[50];

        time_t now = time(nullptr);

        strftime(date_t, 50, "%x %X", localtime(&now));
        std::cout << date_t  << " [" << log_level_trans.toString(level) << "]" << ":"<< content << std::endl;
    }
};