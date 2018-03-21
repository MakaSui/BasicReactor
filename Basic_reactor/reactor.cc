//
// Created by parallels on 3/18/18.
//
//
// Created by hatter on 2018/3/20.
//

#include <sys/epoll.h>
#include <cstring>
#include "reactor.h"
#include "error_handle.h"



Reactor::Reactor() = default;

Reactor::Reactor(int listenfd) {
    this->listenfd = listenfd;
    this->epollfd = create_epollfd();
    event_demultiplexer = new Event_Demultiplexer(epollfd);
    event_handle = new Event_Handle();
}
Reactor::~Reactor() {
    delete event_demultiplexer;
    delete event_handle;
}

void Reactor::handle_events() {
    Reactor::register_handle(epollfd, listenfd, EPOLLIN);
    for( ; ; ){
        event_demultiplexer->wait_event(listenfd, event_handle);
    }
}

void Reactor::register_handle(int efd, int fd, int events) {
    EpollCtl(efd, EPOLL_CTL_ADD, fd, events);
}

void Reactor::remove_handle(int efd,int fd, int events) {
    EpollCtl(efd, EPOLL_CTL_DEL, fd, events);
}


void Reactor::EpollCtl(int epollfd, int op, int fd, int events){
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = events;
    ev.data.fd = fd;
    if(epoll_ctl(epollfd, op, fd, &ev) < 0)
        err_exit("epoll_ctl error");
}

int Reactor::create_epollfd(){
    int efd;

    if((efd = ::epoll_create(1)) < 0)
        err_exit("epoll_create() error");

    return efd;
}