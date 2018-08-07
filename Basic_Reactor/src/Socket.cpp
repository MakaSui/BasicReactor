//
// Created by parallels on 4/19/18.
//

#include <sys/socket.h>
#include <cerrno>
#include <netinet/in.h>
#include <fcntl.h>
#include "../include/Socket.h"
#include "../include/error_handle.h"




int Sockets::Socket(int family) {
    int listenfd = ::socket(family, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);

    if (listenfd == -1)
        err_exit("Sockets::Socket() error");

    return listenfd;
}

void Sockets::Bind(int sockfd, const struct sockaddr *myaddr) {
    if (::bind(sockfd, myaddr, static_cast<socklen_t>(sizeof(struct sockaddr))))
        err_exit("Sockets::Bind() error");
}

void Sockets::Listen(int sockfd) {
    int backlog = 1024;
    if (::listen(sockfd, backlog) == -1)
        err_exit("Sockets::Listen() error");
}

int Sockets::Accept(int sockfd, struct sockaddr *addr) {
    socklen_t addrlen = sizeof(addr);
    int connfd = ::accept4(sockfd, addr, &addrlen, SOCK_NONBLOCK | SOCK_CLOEXEC);

    if (connfd < 0) {
        int savedErrno = errno;
        err_exit("Socket::accept");
        switch (savedErrno) {
            case EAGAIN:
            case ECONNABORTED:
            case EINTR:
            case EPROTO: // ???
            case EPERM:
            case EMFILE: // per-process lmit of open file desctiptor ???
                // expected errors
                errno = savedErrno;
                break;
            case EBADF:
            case EFAULT:
            case EINVAL:
            case ENFILE:
            case ENOBUFS:
            case ENOMEM:
            case ENOTSOCK:
            case EOPNOTSUPP:
                // unexpected errors
                err_exit("unexpected error of ::accept");
                break;
            default:
                err_exit("unknown error of ::accept");
                break;
        }
    }
    return connfd;

}

void Sockets::shutdownWrite(int sockfd) {
    if (::shutdown(sockfd, SHUT_WR) < 0) {
        err_exit("sockets::shutdownWrite");
    }
}

void Sockets::Close(int sockfd) {
    if (::close(sockfd) == -1)
        err_exit("close error");
}

void Sockets::setReuseAddr(int sockfd, bool on) {
    int optval = on ? 1 : 0;
    int ret = ::setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, static_cast<socklen_t>(sizeof optval));
    if (ret < 0) {
        err_exit("SO_REUSEADDR failed.");
    }
}

void Sockets::setReusePort(int sockfd, bool on) {
    int optval = 1;
    int ret = ::setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &optval, static_cast<socklen_t>(sizeof optval));
    if (ret < 0) {
        err_exit("SO_REUSEPORT failed.");
    }
}

void Sockets::setKeepAlive(int sockfd, bool on) {
    int optval = 1;
    int ret = ::setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &optval, static_cast<socklen_t>(sizeof optval));
    if (ret < 0) {
        err_exit("SO_KEEPALIVE failed.");
    }
}

void Sockets::set_nonblocking(int fd){
    int flags;

    if( (flags = fcntl(fd, F_GETFL,0)) < 0)
        err_exit("fcntl() error");

    if(fcntl(fd, F_SETFL, flags|O_NONBLOCK) < 0)
        err_exit("fcntl() error");
}


ssize_t Sockets::Recv(int sockfd, void *buff, size_t nbytes, int flags) {
    ssize_t n;
    if((n=recv(sockfd,buff,nbytes,flags))<0)
        err_exit("recv() error");
    return n;
}