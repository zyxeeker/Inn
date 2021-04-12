//
// Created by ZYXeeker on 2021/4/9.
//

#ifndef INN_AUTH_H
#define INN_AUTH_H

#include <mysql/mysql.h>
#include <iostream>
#include <unordered_map>

class Auth {
public:
    Auth(MYSQL *conn) : m_mysql_conn(conn) {
        mysql_query(m_mysql_conn, "SELECT username,passwd FROM user");
        //从表中检索完整的结果集
        MYSQL_RES *result = mysql_store_result(m_mysql_conn);
        //返回结果集中的列数
        int num_fields = mysql_num_fields(result);
        //返回所有字段结构的数组
        MYSQL_FIELD *fields = mysql_fetch_fields(result);
        //从结果集中获取下一行，将对应的用户名和密码，存入map中
        while (MYSQL_ROW row = mysql_fetch_row(result)) {
            std::string temp1(row[0]);
            std::string temp2(row[1]);
            m_users[temp1] = temp2;
        }
    };

    bool insert_user(std::string user, std::string pwd);

    std::unordered_map<std::string, std::string> get_result() { return m_users; }

private:
    MYSQL *m_mysql_conn;

    std::unordered_map<std::string, std::string> m_users;
};

class Login : public Auth {
public:
    Login(MYSQL *conn) : Auth(conn) {};

    int login_confirm(std::string user, std::string pwd);

private:
    std::unordered_map<std::string, std::string> m_users;

};

class Reg : public Auth {
public:
    Reg(MYSQL *conn) : Auth(conn) {};

    int reg_confirm(std::string user, std::string pwd);
};

#endif //INN_AUTH_H
