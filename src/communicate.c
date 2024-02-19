//
// Created by shobhit on 19/2/24.
//

#include "communicate.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

char* printRecvdData(int communicateSock_fd) {
    char buff[256] = {0};
    int len = recv(communicateSock_fd, buff, 256, 0);
    printf("%s\n", buff);
    if(len == -1) {
        perror("Error\n");
    }
    return buff;
}
