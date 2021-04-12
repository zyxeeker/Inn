//
// Created by ibuprofenlz on 2021/4/6.
//
#ifndef INN_USER_H
#define INN_USER_H

#include <unordered_map>

class user {
public:
    user();

    void SetBaseInformation();

    void SetAccountInfo();

    void PrintInfo();

    int LogIn();

    int SendMessage();

    int Exit();

public:
    // 用户总列表
    static std::unordered_map<std::string, int> user_socket;

private:
    char m_u_id[20];
    char m_u_name[10];
    char m_u_password[20];
    char m_Intro[200];

};

#endif //INN_USER_H

