//
// Created by zyxeeker on 12/20/21.
//

#include "conf.h"
#include <unistd.h>
#include <cstdio>
#include "Meta/tools/logger.h"

Meta::ServerConfig *Meta::ServerConfig::server_setting_ = nullptr;

int Meta::ServerConfig::ReadConfigFile() {
    m_server_config = new server_config{};
    if (access("../config.yaml", F_OK) == -1) {
        LOG_E("Cannot find config.yaml!");
        return -1;
    }
    try {
        m_config = YAML::LoadFile("../config.yaml");
    } catch (...) {
        LOG_E("Open config.yaml failed!");
        return -1;
    }
    if (m_config.IsNull()) {
        LOG_E("config.yaml is empty!");
        return -1;
    } else if (m_config["server"]) {
        ReadValue("port", m_server_config->port);
        ReadValue("event_num", m_server_config->event_num);
        ReadValue("listen_num", m_server_config->listen_num);
        return 0;
    }
    return -1;
}

server_config *Meta::ServerConfig::Settings() {
    return m_server_config;
}

template<class T>
void Meta::ServerConfig::ReadValue(const char *key, T &t) const {
    if (m_config["server"][key])
        t = m_config["server"][key].template as<T>();
}