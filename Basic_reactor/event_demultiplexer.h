//
// Created by parallels on 3/18/18.
//

#ifndef BASIC_REACTOR_ACCEPTOR_H
#define BASIC_REACTOR_ACCEPTOR_H


#include "event_handle.h"

class Event_Handle;

class Event_Demultiplexer{
    int epollfd;
    int number;
public:

    explicit Event_Demultiplexer(int efd);
    ~Event_Demultiplexer();

    int wait_event(int sockfd, Event_Handle *event_handle);

};

#endif //BASIC_REACTOR_ACCEPTOR_H
