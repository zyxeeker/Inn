//
// Created by ZYXeeker on 2021/4/10.
//

#include "router.h"

void Router::init(int epoll_fd, int sock_fd, std::string text) {
    m_epoll_fd = epoll_fd;
    m_sock_fd = sock_fd;
    m_text = text;
}

void Router::do_req(MYSQL *conn) {
    Login login(conn);
    Reg reg(conn);
    if (!m_text.find("LOGIN", 0)) {
        m_text = m_text.substr(6);
        std::string user;
        std::string pwd;
        for (int i = 0; i != m_text.size(); ++i) {
            if (m_text[i] == ' ') {
                user = m_text.substr(0, i);
                pwd = m_text.substr(i + 1);
                break;
            }
        }

        if (login.confirm(user, pwd) != 0) {
            conn_pool::conns::epoll_mod(m_epoll_fd, m_sock_fd, EPOLLOUT | EPOLLET);
            m_message = "用户名/密码错误";
            return;
        } else
            conn_pool::conns::epoll_mod(m_epoll_fd, m_sock_fd, EPOLLOUT | EPOLLET);
        m_message = "登陆成功！";
    }

    if (!m_text.find("REG", 0)) {
        m_text = m_text.substr(4);
        std::string user;
        std::string pwd;
        for (int i = 0; i != m_text.size(); ++i) {
            if (m_text[i] == ' ') {
                user = m_text.substr(0, i);
                pwd = m_text.substr(i + 1);
                break;
            }
        }

        if (reg.confirm(user, pwd) != 0) {
            conn_pool::conns::epoll_mod(m_epoll_fd, m_sock_fd, EPOLLOUT | EPOLLET);
            m_message = "用户名已存在！";
            return;
        } else
            conn_pool::conns::epoll_mod(m_epoll_fd, m_sock_fd, EPOLLOUT | EPOLLET);
        m_message = "注册成功！";
    }
}