//
// Created by parallels on 4/19/18.
//

#include <memory>
#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include "TcpEventHandle.h"
#include "error_handle.h"

TcpEventHandle::TcpEventHandle(EventLoopThreadPool *&threadPool)
        : threadPool_(threadPool)
{

}

void TcpEventHandle::handleRead(int epollfd, int fd, struct epoll_event client) {
    this->epollfd = epollfd;
    this->r_fd = fd;
    this->client = client;

    //read_();
    threadPool_->run(std::bind(&TcpEventHandle::read_,this));
}

void TcpEventHandle::handleWrite(int fd){
    this->w_fd = fd;

    //write_();
    threadPool_->run(std::bind(&TcpEventHandle::write_,this));
}

void TcpEventHandle::handleError() {
    err_exit("unknow event");
}

void TcpEventHandle::read_() {
    ssize_t n;
    again:

    while((n = recv(r_fd,buf, sizeof(buf), 0)) > 0){
        std::cout<<"read msg: "<< buf<<std::flush;
    }
    if (n <0 && errno == EINTR)
        goto again;

    if (n < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)){
        return;
    }

    if (n < 0){
        std::cout<<"read() error"<<std::endl;
    }

    epoller.remove_handle(r_fd, epollfd);

    close(r_fd);
    std::cout<<"client shutdown！！！"<<std::endl;


}

void TcpEventHandle::write_() {
    char* readbuf;
    write(w_fd, readbuf, sizeof(readbuf));
}

void TcpEventHandle::send_() {

}

