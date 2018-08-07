//
// Created by parallels on 4/19/18.
//

#ifndef BASIC_REACTOR_NEW_TCPEVENTHANDLE_H
#define BASIC_REACTOR_NEW_TCPEVENTHANDLE_H

#include <sys/epoll.h>
#include "EventLoopThreadPool.h"
#include "Epoller.h"

class TcpEventHandle {
public:
    TcpEventHandle(EventLoopThreadPool *&threadPool);

    void handleRead(int epollfd, int fd, struct epoll_event client);
    void handleWrite(int fd);
    void handleClose();
    void handleError();
    void handleSendMessage();

    std::shared_ptr<char> buf = std::make_shared<char>();
    //char buf[4096];

private:
    int epollfd;
    int r_fd;
    int w_fd;
    struct epoll_event client;
    Epoller epoller;
    EventLoopThreadPool *threadPool_;

    void read_();
    void write_();
    void send_();

};

#endif //BASIC_REACTOR_NEW_TCPEVENTHANDLE_H
