//
// Created by ZYXeeker on 2021/4/9.
//

#include <string>
#include <map>
#include "auth.h"
#include "../conn/conn.h"

enum AUTH_STATUE {
    CORRECT,
#define CORRECT CORRECT
    UP_ERROR,
#define UP_ERROR UP_ERROR
    P_ERROR,
#define P_ERROR P_ERROR
};


int Auth::test(MYSQL *conn, std::string user, std::string pwd) {
    std::map<std::string, std::string> users;
    mysql_query(conn, "SELECT username,passwd FROM user");
    //从表中检索完整的结果集
    MYSQL_RES *result = mysql_store_result(conn);
    //返回结果集中的列数
    int num_fields = mysql_num_fields(result);
    //返回所有字段结构的数组
    MYSQL_FIELD *fields = mysql_fetch_fields(result);
    //从结果集中获取下一行，将对应的用户名和密码，存入map中
    while (MYSQL_ROW row = mysql_fetch_row(result)) {
        std::string temp1(row[0]);
        std::string temp2(row[1]);
        users[temp1] = temp2;
    }
    if (users.find(user) == users.end())
        return UP_ERROR;
    else if (users[user] != pwd)
        return P_ERROR;

    return CORRECT;

}
