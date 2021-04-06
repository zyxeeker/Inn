//
// Created by ZYXeeker on 2021/4/6.
//

#ifndef INN_LOGGER_H
#define INN_LOGGER_H

#include <string>
#include <ctime>

namespace Log{
    // 日志等级
    struct log_level {
        enum level{
            UNKNOWN,
            DEBUG,
            INFO,
            WARN,
            ERROR,
            FATAL
        };
        std::string toString(log_level::level);
    };

    // 日志生成器
    class logger {
    public:
        logger(log_level::level, std::string content);

    private:
        log_level log_level_trans;
        std::string m_content;
    };
}
#endif //INN_LOGGER_H
