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

std::unordered_map<std::string, int> user::user_socket;

user::user() {

    std::cout << "一个纯路人用户出现";
}

int user::LogIn() {
    return 0;
}

int user::SendMessage() {
    return 0;
}

void user::SetBaseInformation() {
    std::cout << "请输入ID:";
    std::cin >> m_u_id;
    std::cout << "请设置您的密码:";
    std::cin >> m_u_password;
    std::cout << "请输入您的名字:";
    std::cin >> m_u_name;
    std::cout << "请输入您的个人简介:";
    std::cin >> m_Intro;

}

void user::PrintInfo() {
    std::cout << m_u_name << std::endl;
    std::cout << m_u_id << std::endl;
    std::cout << m_Intro << std::endl;
}
//void user::RequestConnect() {
//    ClintConnect();
//
//}
//user::user all_users[MAX_USER_NUMBER];
//int users_number;

