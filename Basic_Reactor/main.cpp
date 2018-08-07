#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include "include/error_handle.h"
#include "include/TcpServer.h"

int main(int argc, char* argv[]) {
    int listenfd,reuse;
    struct sockaddr_in servaddr;

    if (argc != 3)
        err_exit("usage: <iPaddress> <Port>");

    const char *ip = argv[1];
    int port = strtol(argv[2], NULL, 10);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);

    if(::inet_pton(AF_INET, ip, &servaddr.sin_addr) == -1)
        err_exit("inet_pton() error");

    TcpServer tcpServer(servaddr);

    tcpServer.startLoop();

    return 0;
}
