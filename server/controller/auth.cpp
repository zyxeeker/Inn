//
// Created by ZYXeeker on 2021/4/9.
//

#include <string>
#include <map>
#include "auth.h"
#include "../conn/conn.h"

enum LOGIN_STATUE {
    CORRECT,
#define CORRECT CORRECT
    UP_ERROR,
#define UP_ERROR UP_ERROR
    P_ERROR,
#define P_ERROR P_ERROR
};

enum REG_STATUE {
    U_ERROR = 1,
#define U_ERROR U_ERROR
};

bool Auth::insert_user(std::string user, std::string pwd) {
    std::string query_tmp = "INSERT INTO user (username, passwd) VALUES (\"" + user + "\", \"" + pwd + "\");";

    mysql_query(m_mysql_conn, query_tmp.c_str());
}

int Login::login_confirm(std::string user, std::string pwd) {
    std::unordered_map<std::string, std::string> users;
    users = get_result();
    if (users.find(user) == users.end())
        return UP_ERROR;
    else if (users[user] != pwd)
        return P_ERROR;

    return CORRECT;
}


int Reg::reg_confirm(std::string user, std::string pwd) {
    std::unordered_map<std::string, std::string> users;
    users = get_result();
    if (users.find(user) == users.end()) {
        insert_user(user, pwd);
        return CORRECT;
    } else
        return U_ERROR;
}