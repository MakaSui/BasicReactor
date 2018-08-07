//
// Created by parallels on 4/19/18.
//

#ifndef BASIC_REACTOR_NEW_EVENTLOOP_H
#define BASIC_REACTOR_NEW_EVENTLOOP_H

#include "Epoller.h"
#include "Channel.h"

class EventLoop {
public:
    EventLoop();
    explicit EventLoop(EventLoopThreadPool *&threadPool);
    ~EventLoop();
    void loop();
    void runInLoop(int listenfd);

private:
    Epoller *epoller;
    Channel *channel;
    int listenfd_;
    int epollfd_;
    bool looping_;
    bool quit_;
    int number_;
    int new_fd,new_events;
    struct epoll_event events;
    EventLoopThreadPool *threadPool_;
};

#endif //BASIC_REACTOR_NEW_EVENTLOOP_H
