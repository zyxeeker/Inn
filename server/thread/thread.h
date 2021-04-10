//
// Created by ZYXeeker on 2021/4/8.
//

#ifndef INN_THREAD_H
#define INN_THREAD_H

#include <pthread.h>
#include "locker.h"
#include <list>
#include "../controller/sql.h"


template<typename T>
class thread_pool {
public:
    thread_pool(SQL::conn_pool *pool, int thread_num = 20, int request_num = 20);

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

    SQL::conn_pool *m_test;


};

template<typename T>
thread_pool<T>::thread_pool(SQL::conn_pool *pool, int thread_num, int request_num) :
        m_test(pool), m_THREAD_NUM(thread_num), m_MAX_REQUEST_NUM(request_num) {

//    SQL::conn_pool test("localhost", "root", "123456", 25);
//
//    test.init();
//    m_test = &test;

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

//    SQL::conn_pool test("localhost", "root", "123456", 25);
//    test.init();

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

//        req->do_request();
        MYSQL *conn = m_test->get_avail_conn();
        req->test(conn);
    }
}

#endif //INN_THREAD_H