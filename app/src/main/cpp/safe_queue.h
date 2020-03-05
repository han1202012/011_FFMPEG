#ifndef DNRECORDER_SAFE_QUEUE_H
#define DNRECORDER_SAFE_QUEUE_H

#include <queue>
#include <pthread.h>

using namespace std;

/*
    SafeQueue 是一个模板类
        在该模板类中 , 将队列的操作进行了一系列线程安全封装
        所有的对类的修改 , 都在线程安全的条件下执行的
 */
template<typename T>
class SafeQueue {
    typedef void (*ReleaseHandle)(T &);

    typedef void (*SyncHandle)(queue<T> &);

public:
    SafeQueue() {
        pthread_mutex_init(&mutex, NULL);
        pthread_cond_init(&cond, NULL);
    }

    ~SafeQueue() {
        pthread_cond_destroy(&cond);
        pthread_mutex_destroy(&mutex);
    }

    void push(const T new_value) {

        pthread_mutex_lock(&mutex);
        if (work) {
            q.push(new_value);
            pthread_cond_signal(&cond);
            pthread_mutex_unlock(&mutex);
        }
        pthread_mutex_unlock(&mutex);

    }


    int pop(T& value) {
        int ret = 0;


        pthread_mutex_lock(&mutex);

        //工作的标志为 1 , 并且当前队列为空 , 开始等待
        while (work && q.empty()) {
            pthread_cond_wait(&cond, &mutex);
        }

        if (!q.empty()) {
            value = q.front();
            q.pop();
            ret = 1;
        }
        pthread_mutex_unlock(&mutex);

        return ret;
    }

    /**
     * 设置当前是否工作
     * @param work
     */
    void setWork(int work) {

        pthread_mutex_lock(&mutex);
        this->work = work;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);

    }

    int empty() {
        return q.empty();
    }

    int size() {
        return q.size();
    }

    void clear() {

        pthread_mutex_lock(&mutex);
        int size = q.size();
        for (int i = 0; i < size; ++i) {
            T value = q.front();
            releaseHandle(value);
            q.pop();
        }
        pthread_mutex_unlock(&mutex);

    }

    /**
     * 线程安全的前提下 , 让队列使用者使用队列使用该队列
     *      调用该方法 , 能够保证操作 queue 队列时是在同步块中执行的
     */
    void sync() {

        pthread_mutex_lock(&mutex);
        syncHandle(q);
        pthread_mutex_unlock(&mutex);

    }

    void setReleaseHandle(ReleaseHandle r) {
        releaseHandle = r;
    }

    void setSyncHandle(SyncHandle s) {
        syncHandle = s;
    }

private:


    pthread_cond_t cond;
    pthread_mutex_t mutex;

    queue<T> q;

    /**
     * 工作标记
     *      该标记设置为 1 , 才开始工作
     *      如果设置为 0 , 不工作
     */
    int work;

    ReleaseHandle releaseHandle;
    SyncHandle syncHandle;

};


#endif //DNRECORDER_SAFE_QUEUE_H
