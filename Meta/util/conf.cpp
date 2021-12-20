//
// Created by zyxeeker on 12/20/21.
//

#include "conf.h"
#include "yaml-cpp/yaml.h"
#include "Meta/tools/logger.h"

Meta::ServerConfig *Meta::ServerConfig::server_setting_ = nullptr;

int Meta::ServerConfig::ReadConfigFile() {
    YAML::Node config;
    m_server_config = new server_config{};
    try {
        config = YAML::LoadFile("../config.yaml");
    } catch (...) {
        LOG_E(__FUNCTION__, "Cannot find config.yaml!");
        return -1;
    }
    if (config.IsNull()) {
        LOG_E(__FUNCTION__, "config.yaml is empty!");
        return -1;
    } else {
        m_server_config->port = config["server"]["port"].as<int>();
        m_server_config->event_num = config["server"]["event_num"].as<int>();
        m_server_config->listen_num = config["server"]["listen_num"].as<int>();
    }
}

server_config *Meta::ServerConfig::Settings() {
    return m_server_config;
}