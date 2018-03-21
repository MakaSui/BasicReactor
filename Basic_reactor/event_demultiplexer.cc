//
// Created by parallels on 3/18/18.
//

#include <sys/epoll.h>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include "event_demultiplexer.h"
#include "error_handle.h"


Event_Demultiplexer::Event_Demultiplexer(int efd) {
    epollfd = efd;

}

Event_Demultiplexer::~Event_Demultiplexer() {
    ::close(epollfd);
}

int Event_Demultiplexer::wait_event(int sockfd, Event_Handle *event_handle) {
    int new_fd,new_events;
    const int max_epoll_events = 20;
    struct epoll_event events[100];
    int waitms = 10000;
    char *read_buf = NULL;
    
    if((number = epoll_wait(epollfd, events, max_epoll_events, waitms)) < 0)
        err_exit("epoll_wait() error");

    for (int i = 0; i < number; i++) {
        new_fd = events[i].data.fd;
        new_events = events[i].events;
        if(new_events & (EPOLLIN | EPOLLERR)) {
            if (new_fd == sockfd) {  // new accept
                std::cout<<"new accept!!!!"<<std::endl;
           
                event_handle->handle_accept(epollfd, new_fd);
            }
            else{ // read
                read_buf = event_handle->handle_read(epollfd, new_fd, events[i]);
            }
        }
        else if(new_events & EPOLLOUT) { //write
            std::cout<<"handling epollout"<<std::endl;
            event_handle->handleWrite(read_buf, new_fd);
        }
        else{
            err_exit("unknow event");
        }

    }

    return number;
}

