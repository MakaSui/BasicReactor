//
// Created by parallels on 4/19/18.
//

#ifndef BASIC_REACTOR_NEW_CHANNEL_H
#define BASIC_REACTOR_NEW_CHANNEL_H


#include "TcpEventHandle.h"
#include "Acceptor.h"

class Channel {
public:
    Channel(int sockfd, int epollfd, EventLoopThreadPool *&threadPool);
    ~Channel();
    void handleEvent(struct epoll_event events);

private:
    int sockfd_;
    int epollfd_;
    TcpEventHandle *eventHandle;
    Acceptor *acceptor;
};



#endif //BASIC_REACTOR_NEW_CHANNEL_H
