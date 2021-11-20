//
// Created by zyxeeker on 11/20/21.
//

#ifndef INN_META_THREAD_THREAD_H_
#define INN_META_THREAD_THREAD_H_

#include <pthread.h>
#include <semaphore.h>
#include <list>

namespace Meta {
    template<typename T>
    class ThreadPool {
    public:
        ThreadPool(int pThreadNum = 20);
        ~ThreadPool();
        void AppendTask(T *task);
    private:
        static void *Task(void *arg);
        void RunTask();
    private:
        pthread_mutex_t *m_mutex = nullptr;
        sem_t *m_sem = nullptr;
        std::list<T *> m_tasks;
        pthread_t *m_threads = nullptr;
    };

    template<typename T>
    ThreadPool<T>::ThreadPool(int pThreadNum) {
        m_threads = new pthread_t[pThreadNum];
        pthread_mutex_init(m_mutex, nullptr);
        sem_init(m_sem, NULL, NULL);

        for (int i = 0; i < pThreadNum; ++i) {
            if (pthread_create(m_threads + i, nullptr, Task, this))
                delete[]m_threads;
            pthread_detach(m_threads[i]);
        }
    }

    template<typename T>
    ThreadPool<T>::~ThreadPool() {
        pthread_mutex_destroy(m_mutex);
        sem_destroy(m_sem);
    }

    template<typename T>
    void ThreadPool<T>::AppendTask(T *task) {
        pthread_mutex_lock(m_mutex);
        m_tasks.push_back(task);
        pthread_mutex_unlock(m_mutex);
        sem_post(m_sem);
    }

    template<typename T>
    void *ThreadPool<T>::Task(void *arg) {
        auto *t = reinterpret_cast<ThreadPool<T> *>(arg);
        std::cout << pthread_self() << std::endl;
        return t;
    }

    template<typename T>
    void ThreadPool<T>::RunTask() {
        sem_wait(m_sem);
    }

}

#endif //INN_META_THREAD_THREAD_H_
