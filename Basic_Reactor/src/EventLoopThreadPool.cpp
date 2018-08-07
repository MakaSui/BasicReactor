//
// Created by hatter on 2018/4/21.
//

#include "../include/EventLoopThreadPool.h"


EventLoopThreadPool::EventLoopThreadPool()
        : start_(false),
          maxQueueSize_(0)
{}

EventLoopThreadPool::~EventLoopThreadPool() {
    stop();
}

void EventLoopThreadPool::start(int thread_num) {
    assert(!start_);

    start_ = true;

    thread_.reserve(thread_num);

    for(int i=0; i < thread_num; ++i) {
        thread_.emplace_back(std::thread(&EventLoopThreadPool::runInThread,this));
    }

}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
void EventLoopThreadPool::run(std::function<void()>&& task) {
    if(thread_.empty()) {
        task();
    }
    else {
        // queue full
        std::unique_lock<std::mutex> lock(mutex_);
        notFull_.wait(lock,[this]{return !isFull();});

        assert(!isFull());
        queue_.push(std::move(task));
        notEmpty_.notify_one();
    }
}
#else
void EventLoopThreadPool::run(const std::function<void(void)>& task) {
        if(thread_.empty()) {
            task();
        }
        else {
            // queue full
            std::unique_lock<std::mutex> lock(mutex_);
            notFull_.wait(lock,[this]{return !isFull();});

            assert(!isFull());
            queue_.push(task);
            notEmpty_.notify_one();
        }
    }
#endif

std::function<void()> EventLoopThreadPool::take() {
    // start && queue empty
    std::unique_lock<std::mutex> lock(mutex_);
    notEmpty_.wait(lock, [this] { return !queue_.empty() || !start_; });

    std::function<void()> task;

    if (!queue_.empty()) {
        task = queue_.front();
        queue_.pop();
        if (maxQueueSize_ > 0) {
            notFull_.notify_one();
        }
    }

    return task;
}

void EventLoopThreadPool::stop() {
    {
        std::unique_lock<std::mutex> lock(mutex_);
        start_ = false;
        notEmpty_.notify_all();
    }
    for_each(thread_.begin(), thread_.end(), std::mem_fn(&std::thread::join));
}

void EventLoopThreadPool::runInThread(){
    try {
        while (start_) {
            std::function<void()> task(take());
            if(task) {
                task();
            }
        }
    }
    catch (const std::exception& ex)
    {
        fprintf(stderr, "reason: %s\n", ex.what());
        abort();
    }
    catch (...)
    {
        throw; // rethrow
    }

}

bool EventLoopThreadPool::isFull() {
    return maxQueueSize_ > 0 && queue_.size() >= maxQueueSize_;
}