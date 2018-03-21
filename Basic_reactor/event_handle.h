//
// Created by parallels on 3/18/18.
//

#ifndef BASIC_REACTOR_EVENT_HANDLE_H
#define BASIC_REACTOR_EVENT_HANDLE_H

#include <sys/epoll.h>
#include "reactor.h"

class Reactor;

class Event_Handle{
public:
    Reactor *reactor_;

    Event_Handle();
    ~Event_Handle();

    char *handle_read(int epollfd, int fd, struct epoll_event client);
    void handleWrite(char *readbuf, int fd);
    void handle_accept(int epollfd, int fd);
};

#endif //BASIC_REACTOR_EVENT_HANDLE_H
