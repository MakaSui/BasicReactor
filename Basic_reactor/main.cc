#include <iostream>
#include <unistd.h>
#include "error_handle.h"
#include "reactor.h"
#include "tcp_listen.h"
#include "set_nonblocking.h"


int main(int argc, char *argv[]) {
    int listenfd;

    if(argc != 3)
        err_exit("usage: <IPaddress> <port>");

    int port = strtol(argv[2], NULL, 10);
    listenfd = tcp_listen(argv[1], port);  // create listen fd
    printf("socket create success!\n");
    Reactor reactor(listenfd);
    set_nonblocking(listenfd);
    reactor.handle_events();

    close(listenfd);

    return 0;
}

