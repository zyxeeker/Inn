//
// Created by zyxeeker on 11/18/21.
//

#include <iostream>
#include "logger.h"

char *Meta::trans(LOG_LEVEL level) {
    switch (level) {
#define TRANS(level) \
    case LOG_LEVEL::level: \
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

Meta::Logger *Meta::Logger::m_l = nullptr;

void Meta::Logger::out(LOG_LEVEL level, const char *func, const char *msg) {
    std::cout << __DATE__ << " " << __TIME__ << " [" << trans(level) << "](" << func << "):" << msg << std::endl;
}
