//
// Created by zyxeeker on 12/20/21.
//

#ifndef INN_META_UTIL_CONF_H_
#define INN_META_UTIL_CONF_H_

#include "Meta/model/define.h"

#ifndef GET_META_CONF
#define GET_META_CONF Meta::ServerConfig::Instance()->Instance()->Settings()
#endif

namespace Meta {
    class ServerConfig {
    public:
        static ServerConfig *Instance() {
            if (!server_setting_)
                server_setting_ = new ServerConfig;
            return server_setting_;
        }
        server_config *Settings();
        int ReadConfigFile();
    private:
        static ServerConfig *server_setting_;
        server_config *m_server_config = nullptr;
    };
}

#endif //INN_META_UTIL_CONF_H_
