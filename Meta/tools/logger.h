//
// Created by zyxeeker on 11/18/21.
//

#ifndef INN_LOGGER_H
#define INN_LOGGER_H

#define LOG(x) do{ Meta::Logger::Instance()->out(INFO,__FUNCTION__,x);}while(0)
#define LOG_D(x) do{ Meta::Logger::Instance()->out(DEBUG,__FUNCTION__,x);}while(0)
#define LOG_W(x) do{ Meta::Logger::Instance()->out(WARN,__FUNCTION__,x);}while(0)
#define LOG_E(x) do{ Meta::Logger::Instance()->out(ERROR,__FUNCTION__,x);}while(0)
#define LOG_F(x) do{ Meta::Logger::Instance()->out(FATAL,__FUNCTION__,x);}while(0)
#define LOG_U(x) do{ Meta::Logger::Instance()->out(UNKNOWN,__FUNCTION__,x);}while(0)

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
