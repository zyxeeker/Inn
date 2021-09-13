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
        m_conn = conn;
        switch (ReqParseService::Core(m_text)) {
            case INN_USER_LOGIN: {
                DoLoginReq();
                break;
            }
            case INN_USER_REG: {
                DoRegReq();
                break;
            }
            case INN_USER_CHAT: {
                DoChatReq();
                break;
            }
        }
    }

    void Router::DoLoginReq() {
        Login login(m_conn);
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
            m_message = std::to_string(INN_USER_LOGIN_WRONG);
            return;
        } else
            Inn::ConnPool::EpollMod(m_socketFd, EPOLLOUT | EPOLLET);
        user::user_socket[user_tmp] = m_socketFd;
        m_message = std::to_string(INN_USER_LOGIN_SUC);
    }

    void Router::DoRegReq() {
        Reg reg(m_conn);
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
            m_message = std::to_string(INN_USER_REG_WRONG);
            return;
        } else
            Inn::ConnPool::EpollMod(m_socketFd, EPOLLOUT | EPOLLET);
        m_message = std::to_string(INN_USER_REG_SUC);
    }

    void Router::DoChatReq() {
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
    }

    std::string Router::GetMsg() const {
        return m_message;
    }
}