//
// Created by zyxeeker on 11/22/21.
//

#include <iostream>
#include "Meta/services/net_service.h"
#include "Meta/util/conf.h"

Meta::NetService *k_net_service = nullptr;
pthread_t k_net_service_thread;

void *RunNetService() {
    k_net_service->Run();
}

int InitNetService() {
    char buf[50];
    k_net_service = new Meta::NetService;
    if (k_net_service->CreateSocket()) {
        LOG_E("Failed to create socket!");
        return -1;
    }
    if (k_net_service->BindSocket()) {
        LOG_E("Failed to Bind socket!");
        return -1;
    }
    if (k_net_service->SetListen()) {
        LOG_E("Failed to listen socket!");
        return -1;
    }
    if (k_net_service->InitEpoll()) {
        LOG_E("Failed to init epoll!");
        return -1;
    }
    if (k_net_service->SetSocketNonBlocking()) {
        LOG_E("Failed to set fd to NonBlocking!");
        return -1;
    }
    int rt;
    if ((rt = pthread_create(&k_net_service_thread,
                             nullptr,
                             reinterpret_cast<void *(*)(void *)>(RunNetService),
                             nullptr))) {
        sprintf(buf, "Failed to create net service thread, error id: %d!", rt);
        LOG_E(buf);
        return -1;
    }
    sprintf(buf, "Net service running at %d!", GET_META_CONF->port);
    LOG(buf);
    return 0;
}

int main() {
    if (Meta::ServerConfig::Instance()->ReadConfigFile())
        LOG("Cannot read config file,use default params.");
    if (InitNetService())
        return -1;
    while (1) {}
}