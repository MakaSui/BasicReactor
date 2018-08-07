//
// Created by parallels on 4/19/18.
//

#ifndef BASIC_REACTOR_NEW_EPOLLER_H
#define BASIC_REACTOR_NEW_EPOLLER_H

#include <sys/epoll.h>

class Epoller {
public:
    void register_handle(int fd, int epollfd);
    void register_handle_accept(int fd, int epollfd);
    void remove_handle(int fd, int epollfd);
    int create_epfd();
    int wait(int epollfd);

    struct epoll_event events[100];

private:
    int waitms = 10000;
    const int max_epoll_events = 20;

    void ep_ctl(int epollfd, int op, int fd, int events);
};

#endif //BASIC_REACTOR_NEW_EPOLLER_H
