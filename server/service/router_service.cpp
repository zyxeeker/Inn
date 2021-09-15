//
// Created by ZYXeeker on 2021/4/10.
//

#include "router_service.h"

void Inn::Router::SetDstData(int socketFd, std::string text) {
    m_socketFd = socketFd;
    m_text = text;
}

void Inn::Router::StartService(MYSQL *conn) {
    m_conn = conn;
    switch (ReqParseService::Core(m_text)) {
        case USER_LOGIN:
            DoLoginReq();
            break;
        case USER_REG:
            DoRegReq();
            break;
        case USER_CHAT:
            DoChatReq();
            break;
        case USER_ALIVE:
            DoHeartBeatReq();
            break;
        case USER_LOGOUT:
            DoLogoutReq();
            break;
    }
}

void Inn::Router::DoLoginReq() {
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
    LOGD(user_tmp);
    LOGD(pwd);
    if (login.Confirm(user_tmp, pwd) != LOGIN_SUC) {
        Inn::ConnPool::EpollMod(m_socketFd, EPOLLOUT | EPOLLET);
        m_message = std::to_string(USER_LOGIN_WRONG);
        return;
    } else
        Inn::ConnPool::EpollMod(m_socketFd, EPOLLOUT | EPOLLET);
    user::user_socket[user_tmp] = m_socketFd;
    m_message = std::to_string(USER_LOGIN_SUC);
}

void Inn::Router::DoRegReq() {
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
        m_message = std::to_string(USER_REG_WRONG);
        return;
    } else
        Inn::ConnPool::EpollMod(m_socketFd, EPOLLOUT | EPOLLET);
    m_message = std::to_string(USER_REG_SUC);
}

void Inn::Router::DoChatReq() {
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

void Inn::Router::DoHeartBeatReq() {
    m_message = std::to_string(USER_HEART_BEAT_COPY);
}

void Inn::Router::DoLogoutReq() {
#if SO_DEBUG
    LOGD("LOGOUT")
    LOGD(m_text);
#endif
    std::string pUser = m_text.substr(8, m_text.length() - 7);
    auto pSocket =  user::user_socket.find(pUser);
    if (pSocket != user::user_socket.end()){
        m_message = std::to_string(USER_LOGOUT_SUC);
        user::user_socket.erase(pSocket);
        return;
    }
        m_message = std::to_string(USER_LOGOUT_SUC);
}

std::string Inn::Router::GetMsg() const {
    return m_message;
}
