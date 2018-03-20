//
// Created by parallels on 3/20/18.
//

#ifndef BASIC_REACTOR_TCP_LISTEN_H
#define BASIC_REACTOR_TCP_LISTEN_H

#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include "error_handle.h"

int tcp_listen(const char *ip, int port);

#endif //BASIC_REACTOR_TCP_LISTEN_H
