//
// Created by ZYXeeker on 2021/4/10.
//

#include "router_service.h"

namespace Inn {
    void Router::SetDstData(int socketFd, std::string text) {
        m_socketFd = socketFd;
        m_text = text;
    }

    void Router::StartService(MYSQL *conn) {
        switch (ReqParseService::Core(m_text)) {
            case INN_USER_LOGIN: {
                Login login(conn);
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
                break;
            }
            case INN_USER_REG: {
                Reg reg(conn);
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
                break;
            }
            case INN_USER_CHAT: {
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


    void Router::DoLoginReq(MYSQL *conn) {

    }

    void Router::DoRegReq(MYSQL *conn) {

    }

    void Router::DoChatReq() {

    }
}