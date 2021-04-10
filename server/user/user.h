//
// Created by ibuprofenlz on 2021/4/6.
//
#ifndef INN_USER_H
#define INN_USER_H
namespace user_s {
class user{
public:
    user();
    void SetBaseInformation();
    void SetAccountInfo();
    void PrintInfo();
    int LogIn();
    int SendMessage();
    int Exit();

private:
    char u_id[20];
    char u_name[10];
    char u_password[20];
    char Intro[200];

};

}
#endif //INN_USER_H

