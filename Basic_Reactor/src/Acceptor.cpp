//
// Created by parallels on 4/19/18.
//

#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
#include <memory>
#include "../include/Acceptor.h"
#include "../include/Socket.h"
#include "../include/Epoller.h"
#include "../include/TcpEventHandle.h"

Acceptor::Acceptor(EventLoopThreadPool *&threadPool)
    : threadPool_(threadPool)
{}

Acceptor::Acceptor(const struct sockaddr_in &listenAddr)
        : listenfd(Sockets::Socket(listenAddr.sin_family))
{
    Sockets::setReuseAddr(listenfd, 1);
    Sockets::setReusePort(listenfd, 1);
    Sockets::Bind(listenfd, (struct sockaddr *) &listenAddr);
}

Acceptor::~Acceptor() {
    if(listenfd)
        Sockets::Close(listenfd);
}

int Acceptor::listen() {
    Sockets::Listen(listenfd);
    return listenfd;
}

void Acceptor::handle_read(struct epoll_event events, int sockfd, int epollfd) {
    // accept and read
    int connfd;
    struct sockaddr_in cliaddr, peer;;
    socklen_t alen = sizeof(peer);
    //std::shared_ptr<auto> read_buf = std::make_shared<char>();
    Epoller epoller;
    TcpEventHandle eventHandle(threadPool_);


    if (events.data.fd == sockfd) {  // new accept
        //accept
        connfd = Sockets::Accept(events.data.fd,(struct sockaddr *) &cliaddr);

        ::getpeername(connfd, (struct sockaddr *)&peer, &alen);

        std::cout<<"accept a connection from"<<::inet_ntoa(cliaddr.sin_addr)<<" : "<<cliaddr.sin_port<<std::endl;

        Sockets::set_nonblocking(connfd);

        events.data.fd = connfd;

        epoller.register_handle_accept(connfd, epollfd);

    }
    else{ // read
        //std::shared_ptr<char> read_buf = std::make_shared<char>();
        eventHandle.handleRead(epollfd, events.data.fd, events);
        //read_buf = eventHandle.buf;
    }
}