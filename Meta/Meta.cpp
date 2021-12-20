//
// Created by zyxeeker on 11/22/21.
//

#include <iostream>
#include "Meta/services/net_service.h"
#include "Meta/util/conf.h"

Meta::ServerConfig *k_config = nullptr;

Meta::NetService *k_net_service = nullptr;
pthread_t k_net_service_thread;

void *RunNetService() {
    k_net_service->Run();
}

int InitNetService() {
    k_net_service = new Meta::NetService;
    if (k_net_service->CreateSocket()) {
        LOG_E(__FUNCTION__, "Failed to create socket!");
        return -1;
    }
    if (k_net_service->BindSocket()) {
        LOG_E(__FUNCTION__, "Failed to Bind socket!");
        return -1;
    }
    if (k_net_service->SetListen()) {
        LOG_E(__FUNCTION__, "Failed to listen socket!");
        return -1;
    }
    if (k_net_service->InitEpoll()) {
        LOG_E(__FUNCTION__, "Failed to init epoll!");
        return -1;
    }
    if (k_net_service->SetSocketNonBlocking()) {
        LOG_E(__FUNCTION__, "Failed to set fd to NonBlocking!");
        return -1;
    }
    int rt;
    if ((rt = pthread_create(&k_net_service_thread,
                             nullptr,
                             reinterpret_cast<void *(*)(void *)>(RunNetService),
                             nullptr))) {
        LOG_E(__FUNCTION__, "Failed to create net service thread, error id:" + rt);
        return -1;
    }
    LOG(__FUNCTION__, "Net service start!");
    return 0;
}

int main() {
    Meta::ServerConfig config;
    config.Instance()->ReadConfigFile();
    if (InitNetService())
        return -1;
    while (1) {}
}