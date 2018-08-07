//
// Created by parallels on 4/19/18.
//



#include <cassert>
#include "../include/EventLoop.h"

EventLoop::EventLoop() = default;

EventLoop::EventLoop(EventLoopThreadPool *&threadPool)
        : epoller(new Epoller()),
          epollfd_(epoller->create_epfd()),
          looping_(false),
          quit_(false),
          threadPool_(threadPool)
{
}

EventLoop::~EventLoop() {
    delete(epoller);
}

void EventLoop::loop() {
    assert(!looping_);
    looping_ = true;
    quit_ = false;
    epoller->register_handle(listenfd_,epollfd_);
    while (!quit_) {
        number_ = epoller->wait(epollfd_);

        for (int i = 0; i < number_; ++i) {
//            new_fd = epoller->events[i].data.fd;
//            new_events = epoller->events[i].events;
            events = epoller->events[i];
            channel->handleEvent(events);
        }
    }
}

void EventLoop::runInLoop(int listenfd) {
    listenfd_ = listenfd;
    channel = new Channel(listenfd, epollfd_, threadPool_);
    loop();
}