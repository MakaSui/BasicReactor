//
// Created by parallels on 4/19/18.
//

#include <sys/epoll.h>
#include <iostream>
#include "Channel.h"
#include "error_handle.h"


Channel::Channel(int sockfd, int epollfd, EventLoopThreadPool *&threadPool)
        : sockfd_(sockfd) ,
          epollfd_(epollfd),
          eventHandle(new TcpEventHandle(threadPool)),
          acceptor(new Acceptor(threadPool))
{
}

Channel::~Channel() {
    delete(eventHandle);
    delete(acceptor);
}

void Channel::handleEvent(struct epoll_event events) {
    int new_fd,new_events;
    new_fd = events.data.fd;
    new_events = events.events;
    if(new_events & (EPOLLIN | EPOLLERR)) {
        acceptor->handle_read(events, sockfd_, epollfd_);
    }
    else if(new_events & EPOLLOUT) { //write
        eventHandle->handleWrite(new_fd);
    }
    else{
        eventHandle->handleError();
    }
}