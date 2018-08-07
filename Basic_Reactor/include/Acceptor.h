//
// Created by parallels on 4/19/18.
//

#ifndef BASIC_REACTOR_NEW_ACCEPTOR_H
#define BASIC_REACTOR_NEW_ACCEPTOR_H

#include <sys/epoll.h>
#include "Socket.h"
#include "EventLoopThreadPool.h"

class Acceptor {
public:
    Acceptor(EventLoopThreadPool *&threadPool);
    explicit Acceptor(const struct sockaddr_in& listenAddr);
    ~Acceptor();
    int listen();
    void handle_read(struct epoll_event events, int sockfd, int epollfd);

private:
    int listenfd;
    EventLoopThreadPool *threadPool_;


};

#endif //BASIC_REACTOR_NEW_ACCEPTOR_H
