//
// Created by parallels on 3/20/18.
//

#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include "tcp_listen.h"

int tcp_listen(const char *ip, int port){
    int listenfd,reuse;
    struct sockaddr_in servaddr;

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);

    if(inet_pton(AF_INET, ip, &servaddr.sin_addr) == -1)
        err_exit("inet_pton() error");

    if((listenfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        err_exit("socket() error");

    if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)) == -1)
        err_exit("setsockopt() error");

    if(bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) == -1)
        err_exit("bind() error");

    if(listen(listenfd, 1024) == -1)
        err_exit("listen() error");

    return listenfd;
}