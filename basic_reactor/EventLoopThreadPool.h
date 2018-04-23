//
// Created by parallels on 4/19/18.
//

#ifndef BASIC_REACTOR_NEW_EVENTLOOPTHREADPOOL_H
#define BASIC_REACTOR_NEW_EVENTLOOPTHREADPOOL_H

#include <functional>
#include <condition_variable>
#include <thread>
#include <vector>
#include <cassert>
#include <algorithm>
#include <queue>

class EventLoopThreadPool {
public:

    EventLoopThreadPool();
    ~EventLoopThreadPool();
    void start(int thread_num);
    void stop();
    void run(const std::function<void()> &task);
    bool isFull();
    std::function<void ()> take();
    void runInThread();

private:

    std::vector<std::thread> thread_;

    // the task queue
    std::queue< std::function<void()> > queue_;

    // synchronization
    std::mutex mutex_;
    std::condition_variable notEmpty_;
    std::condition_variable notFull_;

    bool start_;
    size_t maxQueueSize_;
};

#endif //BASIC_REACTOR_NEW_EVENTLOOPTHREADPOOL_H
