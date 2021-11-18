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

void Meta::Logger::out(LOG_LEVEL level, const char *msg) {
    char date_t[50];
    time_t now = time(nullptr);
    strftime(date_t, 50, "%x %X", localtime(&now));
    std::cout << date_t << " [" << trans(level) << "]" << ":" << *msg << std::endl;

}
