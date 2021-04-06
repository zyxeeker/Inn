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
    char Name[20];
    char Sex;
    int Age;
    int Account;
    int Password;
    char Intro[200];

};
}
#endif //INN_USER_H

