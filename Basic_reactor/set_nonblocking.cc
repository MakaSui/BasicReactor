//
// Created by parallels on 3/20/18.
//
#include <fcntl.h>
#include "set_nonblocking.h"

void set_nonblocking(int fd){
    int flags;

    if( (flags = fcntl(fd, F_GETFL,0)) < 0)
        err_exit("fcntl() error");

    if(fcntl(fd, F_SETFL, flags|O_NONBLOCK) < 0)
        err_exit("fcntl() error");
}