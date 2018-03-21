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

    std::cout<<"accept a connection from"<<inet_ntoa(cliaddr.sin_addr)<<" : "<<cliaddr.sin_port<<std::endl;
    
    set_nonblocking(connfd);

    reactor_->register_handle(epollfd, connfd, EPOLLIN | EPOLLET);

}

char *Event_Handle::handle_read(int epollfd, int fd, struct epoll_event client){
    char buf[4096];
    ssize_t n;
    again:
    while((n = recv(fd,buf, sizeof(buf), 0)) > 0){
        std::cout<<"read msg: "<< buf<<std::flush;
        // Event_Handle::handleWrite(buf, fd);
    }
    if (n <0 && errno == EINTR)
        goto again;

    if (n < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)){
        return NULL;
    }

    if (n < 0){
        std::cout<<"read() error"<<std::endl;
    }

    reactor_->remove_handle(epollfd, fd, NULL);

    close(fd);
    std::cout<<"client shutdown！！！"<<std::endl;

    return buf;

}

void Event_Handle::handleWrite(char *readbuf, int fd){
    if(write(fd, readbuf, sizeof(readbuf)) < 0)      // echo
        err_exit("write() error");
}
