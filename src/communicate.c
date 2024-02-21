//
// Created by shobhit on 19/2/24.
//

#include "communicate.h"
#include "connect.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

// returns the pointer to a dynamically created string
// containing the first 256 characters
// make sure to free the memory from the caller side
char* recvdData_dyn(int communicateSock_fd) {
    char *buff = (char*) malloc(256);
    int len = recv(communicateSock_fd, buff, 256, 0);
    //printf("%s\n", buff);
    if(len == -1) {
        perror("Error\n");
    }
    buff[255] = '\0';
    return buff;
}

// assumes the HTTP method is GET
// returns the URL requested in form of an array of character
void readUrlFromGETReq(char *url, uint16_t port_num) {
    // example request line
    // GET /index.html HTTP/1.1

    int sock = estTcpConnection(port_num);
    char *tempBuffer = recvdData_dyn(sock);
    int i = 4;
    while(tempBuffer[i] != '\0' && tempBuffer[i] != ' ') {
        url[i-4] = tempBuffer[i];
        i++;
    }
    url[i-4] = '\0';
}
