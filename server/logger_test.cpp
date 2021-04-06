//
// Created by ZYXeeker on 2021/4/6.
//

#include "logger/logger.h"

int main(){

    Log::logger(Log::log_level::level::INFO,"Server Start...");
    Log::logger(Log::log_level::level::INFO,"");
    for (int i = 0;i<100;++i){}
    Log::logger(Log::log_level::level::INFO,"");

}