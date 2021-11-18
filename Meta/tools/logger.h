//
// Created by zyxeeker on 11/18/21.
//

#ifndef INN_LOGGER_H
#define INN_LOGGER_H

#include "Meta/model/define.h"

namespace Meta {
    static char *trans(LOG_LEVEL level);

    class Logger {
    public:
        static Logger *Instance() {
            if (m_l == nullptr)
                m_l = new Logger;
            return m_l;
        }

        void out(LOG_LEVEL level, const char *msg);

    private:
        static Logger *m_l;
    };

}


#endif //INN_LOGGER_H
