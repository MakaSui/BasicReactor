//
// Created by parallels on 4/19/18.
//

#ifndef BASIC_REACTOR_NEW_SOCKET_H
#define BASIC_REACTOR_NEW_SOCKET_H

#include <unistd.h>

namespace Sockets {

    int Socket(int family);
    void Bind(int sockfd, const struct sockaddr* myaddr);
    void Listen(int sockfd);
    int Accept(int sockfd, struct sockaddr* cliaddr);
    void Close(int sockfd);
    void setReuseAddr(int sockfd, bool on);
    void setReusePort(int sockfd, bool on);
    void setKeepAlive(int sockfd, bool on);
    void shutdownWrite(int sockfd);
    void set_nonblocking(int fd);



}

#endif //BASIC_REACTOR_NEW_SOCKET_H
