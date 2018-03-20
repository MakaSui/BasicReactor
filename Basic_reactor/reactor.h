//
// Created by parallels on 3/18/18.
//

#ifndef BASIC_REACTOR_REACTOR_H
#define BASIC_REACTOR_REACTOR_H


#include "event_demultiplexer.h"
#include "event_handle.h"

class Event_Handle;
class Event_Demultiplexer;

class Reactor{

public:
    Reactor();
    explicit Reactor(int listenfd);
    ~Reactor();
    void handle_events();
    int create_epollfd();
    void register_handle(int efd, int fd, int events);
    void remove_handle(int efd,int fd, int events);
    void EpollCtl(int epollfd, int op, int fd, int events);

private:
    int listenfd,epollfd;
    int number;
    Event_Demultiplexer *event_demultiplexer;
    Event_Handle *event_handle;
};


#endif //BASIC_REACTOR_REACTOR_H
