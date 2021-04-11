//
// Created by ZYXeeker on 2021/4/9.
//

#ifndef INN_AUTH_H
#define INN_AUTH_H

#include <mysql/mysql.h>

class Auth {
public:
    void test(MYSQL *conn);

private:
    static int m_sockfd;
};

class Login : private Auth {

};

class Sign : private Auth {

};

#endif //INN_AUTH_H
