#include <netinet/in.h>
#include "TcpServer.h"//
// Created by parallels on 4/19/18.
//

TcpServer::TcpServer(const struct sockaddr_in &addr)
        : threadPool(new EventLoopThreadPool()),
          loop_(new EventLoop(threadPool)),
          acceptor_(new Acceptor(addr)),
          listenfd(acceptor_->listen())
{
}

TcpServer::~TcpServer() {
    delete(threadPool);
    delete(loop_);
    delete(acceptor_);
}

void TcpServer::startLoop(){
    threadPool->start(0);
    loop_->runInLoop(listenfd);
}