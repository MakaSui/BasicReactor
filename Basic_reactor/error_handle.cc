//
// Created by parallels on 3/20/18.
//
#include <cstdlib>
#include <cstdio>
#include "error_handle.h"

void err_exit(char *msg) {
    perror(msg);
    exit(1);
}