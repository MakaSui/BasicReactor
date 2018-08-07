//
// Created by parallels on 4/19/18.
//
#include <cstring>
#include "../include/Epoller.h"
#include "../include/error_handle.h"



int Epoller::create_epfd() {
    int efd;

    if((efd = ::epoll_create(1)) < 0)
        err_exit("epoll_create() error");

    return efd;
}

void Epoller::ep_ctl(int epollfd, int op, int fd, int events){
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = events;
    ev.data.fd = fd;
    if(::epoll_ctl(epollfd, op, fd, &ev) < 0)
        err_exit("epoll_ctl error");
}

void Epoller::register_handle(int fd, int epollfd) {
    ep_ctl(epollfd, EPOLL_CTL_ADD, fd, EPOLLIN);
}

void Epoller::register_handle_accept(int fd, int epollfd) {
    ep_ctl(epollfd, EPOLL_CTL_ADD, fd, EPOLLIN | EPOLLET);
}

void Epoller::remove_handle(int fd, int epollfd) {
    ep_ctl(epollfd, EPOLL_CTL_DEL, fd, NULL);
}

int Epoller::wait(int epollfd) {
    int number;
    if((number = epoll_wait(epollfd, events, max_epoll_events, waitms)) < 0)
        err_exit("epoll_wait() error");

    return number;
}