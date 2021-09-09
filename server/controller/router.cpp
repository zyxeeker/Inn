//
// Created by ZYXeeker on 2021/4/10.
//

#include "router.h"

namespace Inn {
    void Router::SetDstData(int socketFd, std::string text) {
        m_socketFd = socketFd;
        m_text = text;
    }

    void Router::DoReq(MYSQL *conn) {
        Login login(conn);
        Reg reg(conn);
        if (!m_text.find("LOGIN", 0)) {
            m_text = m_text.substr(6);
            std::string user_tmp;
            std::string pwd;
            for (int i = 0; i != m_text.size(); ++i) {
                if (m_text[i] == ' ') {
                    user_tmp = m_text.substr(0, i);
                    pwd = m_text.substr(i + 1);
                    break;
                }
            }

            if (login.Confirm(user_tmp, pwd) != 0) {
                Inn::ConnPool::EpollMod(m_socketFd, EPOLLOUT | EPOLLET);
                m_message = "用户名/密码错误";
                return;
            } else
                Inn::ConnPool::EpollMod(m_socketFd, EPOLLOUT | EPOLLET);
            user::user_socket[user_tmp] = m_socketFd;
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

            if (reg.Confirm(user, pwd) != 0) {
                Inn::ConnPool::EpollMod(m_socketFd, EPOLLOUT | EPOLLET);
                m_message = "用户名已存在！";
                return;
            } else
                Inn::ConnPool::EpollMod(m_socketFd, EPOLLOUT | EPOLLET);
            m_message = "注册成功！";
        }

        if (!m_text.find("CHAT", 0)) {
            m_text = m_text.substr(5);
            std::string user_tmp;
            std::string text;
            for (int i = 0; i != m_text.size(); ++i) {
                if (m_text[i] == ' ') {
                    user_tmp = m_text.substr(0, i);
                    text = m_text.substr(i + 1);
                    break;
                }
            }

            u2u::send(user_tmp);
            m_message = text;
            return;
        }
    }
}