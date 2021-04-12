#include"user.h"
#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<pthread.h>
#include<sys/epoll.h>
#include<ctype.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include <client/client_connct.h>
#define MAX_USER_NUMBER 1000
namespace user_s {
user_s::user::user(){

    std::cout<<"一个纯路人用户出现";
}

int user_s::user::LogIn(){
    return 0;
}

int user_s::user::SendMessage(){
    return 0;
}
void user_s::user::SetBaseInformation() {
    std::cout<<"请输入ID:";
    std::cin>>u_id;
    std::cout<<"请设置您的密码:";
    std::cin>> u_password;
    std::cout<<"请输入您的名字:";
    std::cin>> u_name;
    std::cout<<"请输入您的个人简介:";
    std::cin>>Intro;

}
void user_s::user::PrintInfo() {
    std::cout<<this->u_name<<std::endl;
    std::cout<<this->u_id<<std::endl;
    std::cout<<this->Intro<<std::endl;
}
void user_s::user::RequestConnect() {
    ClintConnect();

}
user_s::user all_users[MAX_USER_NUMBER];
int users_number;
}
