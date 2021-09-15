//
// Created by ZYXeeker on 2021/4/8.
//

#ifndef INN_THREAD_H
#define INN_THREAD_H

#include <pthread.h>
#include <list>
#include "locker.h"
#include "server/service/sql_service.h"
#include "server/model/define.h"


template<typename T>
class thread_pool {
public:
    thread_pool(Inn::SQLConnPool *pool, int thread_num = 20, int request_num = 20);

    bool append_work(T *req);

    ~thread_pool() { delete[] m_threads; };

private:
    static void *worker(void *args);

    void run();

private:
    // 线程数
    int m_THREAD_NUM;
    // 最大请求数
    int m_MAX_REQUEST_NUM;
    // 线程队列
    std::list<T *> m_work_queue;
    // 线程数组
    pthread_t *m_threads;
    // 锁
    locker m_locker;
    // 信号量
    sem m_sem;

    bool m_run_statue{true};

    int m_st;

    Inn::SQLConnPool *m_mysql_pool;


};

template<typename T>
thread_pool<T>::thread_pool(Inn::SQLConnPool *pool, int thread_num, int request_num) :
        m_mysql_pool(pool), m_THREAD_NUM(thread_num), m_MAX_REQUEST_NUM(request_num) {

    m_threads = new pthread_t[m_THREAD_NUM];

    for (int i = 0; i < m_THREAD_NUM; ++i) {
        if (pthread_create(m_threads + i, nullptr, worker, this) != 0) {
            delete[] m_threads;
        }

        pthread_detach(m_threads[i]);
    }
}


template<typename T>
bool thread_pool<T>::append_work(T *req) {
    m_locker.lock();

    m_work_queue.push_back(req);

    m_locker.unlock();

    m_sem.V();
    return true;
}

template<typename T>
void *thread_pool<T>::worker(void *args) {
    thread_pool *pool = (thread_pool *) args;
    pool->run();
    return pool;
}

template<typename T>
void thread_pool<T>::run() {
    while (m_run_statue) {
        m_sem.P();

        m_locker.lock();

        if (m_work_queue.empty()) {
            m_locker.unlock();
            continue;
        }

        T *req = m_work_queue.front();
        m_work_queue.pop_front();

        m_locker.unlock();

        switch (m_st) {
            case USER_LOGIN:
                break;
            case USER_REG:
                break;
        }

        MYSQL *conn = m_mysql_pool->GetAvailConn();
        req->StartService(conn);
        m_mysql_pool->ReleaseConn(conn);
    }
}

#endif //INN_THREAD_H