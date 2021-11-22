//
// Created by zyxeeker on 11/18/21.
//

#ifndef INN_LOGGER_H
#define INN_LOGGER_H

#define LOG(f, x) Meta::Logger::Instance()->out(INFO,f,x)
#define LOG_D(f, x) Meta::Logger::Instance()->out(DEBUG,f,x)
#define LOG_W(f, x) Meta::Logger::Instance()->out(WARN,f,x)
#define LOG_E(f, x) Meta::Logger::Instance()->out(ERROR,f,x)
#define LOG_F(f, x) Meta::Logger::Instance()->out(FATAL,f,x)
#define LOG_U(f, x) Meta::Logger::Instance()->out(UNKNOWN,f,x)

enum LOG_LEVEL {
    UNKNOWN,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL
};

namespace Meta {
    static char *trans(LOG_LEVEL level);

    class Logger {
    public:
        static Logger *Instance() {
            if (!m_l)
                m_l = new Logger;
            return m_l;
        }

        void out(LOG_LEVEL level, const char *func, const char *msg);
    private:
        static Logger *m_l;
    };

}


#endif //INN_LOGGER_H
