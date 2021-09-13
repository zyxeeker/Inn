//
// Created by ZYXeeker on 2021/4/9.
//

#ifndef INN_AUTH_SERVICE_H
#define INN_AUTH_SERVICE_H

#include <mysql/mysql.h>
#include <iostream>
#include <unordered_map>
#include "server/model/define.h"

class Auth {
public:
    Auth(MYSQL *conn) : m_mysql_conn(conn) { Init(); };

    void Init();

    virtual int Confirm(std::string user, std::string pwd) = 0;

    bool InsertUser(const std::string &user, const std::string &pwd);

    std::unordered_map<std::string, std::string> GetResult() { return m_users; }

private:
    MYSQL *m_mysql_conn;

    std::unordered_map<std::string, std::string> m_users;
};

class Login : public Auth {
public:
    Login(MYSQL *conn) : Auth(conn) {};

    int Confirm(std::string user, std::string pwd) override;

};

class Reg : public Auth {
public:
    Reg(MYSQL *conn) : Auth(conn) {};

    int Confirm(std::string user, std::string pwd) override;

};

#endif //INN_AUTH_SERVICE_H
