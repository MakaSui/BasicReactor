//
// Created by parallels on 3/18/18.
//

#include <unistd.h>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
#include <cerrno>
#include "event_handle.h"
#include "error_handle.h"
#include "set_nonblocking.h"


Event_Handle::Event_Handle() {
    reactor_ = new Reactor();
}

Event_Handle::~Event_Handle() {
    delete(reactor_);
}

void Event_Handle::handle_accept(int epollfd, int fd){
    int connfd;
    struct sockaddr_in cliaddr, peer;
    socklen_t clilen = sizeof(cliaddr);
    socklen_t alen = sizeof(peer);

    if((connfd = accept(fd,(struct sockaddr *) &cliaddr, &clilen)) < 0)
        err_exit("accept() error");

    if(getpeername(connfd, (struct sockaddr *)&peer, &alen) < 0)
        err_exit("getpeername() error");

    printf("accept a connection from %s:%d\n", inet_ntoa(cliaddr.sin_addr),cliaddr.sin_port);
    fflush(stdout);

    set_nonblocking(connfd);

    reactor_->register_handle(epollfd, connfd, EPOLLIN);

}

char *Event_Handle::handle_read(int epollfd, int fd, struct epoll_event client){
    char buf[4096];
    ssize_t n;
    again:
    while((n = read(fd,buf, sizeof(buf))) > 0){
        printf("read msg: %s", buf);
        Event_Handle::handleWrite(buf, fd);
    }
    if (n <0 && errno == EINTR)
        goto again;

    if (n < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)){
        return NULL;
    }

    if (n < 0){
        printf("read() error\n");
    }

    reactor_->remove_handle(epollfd, fd, NULL);

    close(fd);
    printf("client shutdown！！！\n");

    return buf;

}

void Event_Handle::handleWrite(char *readbuf, int fd){
    if(write(fd, readbuf, sizeof(readbuf)) < 0)      // echo
        err_exit("write() error");
}