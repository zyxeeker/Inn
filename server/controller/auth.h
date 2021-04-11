//
// Created by ZYXeeker on 2021/4/9.
//

#ifndef INN_AUTH_H
#define INN_AUTH_H

#include <mysql/mysql.h>
#include <iostream>

class Auth {
public:
    Auth(MYSQL *conn) : m_mysql_conn(conn) {};

    MYSQL *get_conn() { return m_mysql_conn; }

private:
    MYSQL *m_mysql_conn;
};

class Login : public Auth {
public:
    Login(MYSQL *conn) : Auth(conn) {};

    int login_confirm(std::string user, std::string pwd);
};

class Reg : private Auth {
public:
//    int reg_confirm(std::string user, std::string pwd);
};

#endif //INN_AUTH_H
