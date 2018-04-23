//
// Created by parallels on 4/19/18.
//

#ifndef BASIC_REACTOR_NEW_TCPSERVER_H
#define BASIC_REACTOR_NEW_TCPSERVER_H

#include "EventLoop.h"
#include "Acceptor.h"
#include "EventLoopThreadPool.h"

class TcpServer {
public:
    explicit TcpServer(const struct sockaddr_in &addr);
    ~TcpServer();
    void startLoop(); // start loop

    EventLoop *loop_;
    Acceptor *acceptor_;
    EventLoopThreadPool *threadPool;
    int listenfd;
};

#endif //BASIC_REACTOR_NEW_TCPSERVER_H
