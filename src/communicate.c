//
// Created by shobhit on 19/2/24.
//

#include "communicate.h"
#include "connect.h"
#include "read_resource.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// returns the pointer to a dynamically created string
// containing the first 256 characters
// free the memory from the caller side
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

    /*** experimental call ***/
    //sendOKResponse(sock); // experimental function call
    char *msg = readFile_dyn("/home/shobhit/Desktop/temtrdp");
    char final_msg[strlen(msg) + 100];
    strcpy(final_msg, "HTTP/1.1 200 OK\nContent-Length: 100\nContent-Type:text/plain\n\n");
    strcat(final_msg, msg);
    sendCompleteResponse(sock, final_msg);
    /*** end of experimemntal call ***/
}

void sendOKResponse(int sockfd) {
    char *data = "HTTP/1.1 200 OK\nContent-Length: 4\nContent-Type:text/plain\n\npong";
    int len = strlen(data);

    send(sockfd, data, len, 0);
}

// send() doesn't guarantee to send full data at once
// handles partial sends
// exits on error
void sendCompleteResponse(int comm_sockfd, char *msg) {
    int msgLen = strlen(msg);
    int byteSent = 0;
    int n;
    while(byteSent < msgLen) {
        n = send(comm_sockfd, msg + byteSent, msgLen, 0);
        // check if data is sent successfully
        // otherwise exit
        if(n == -1) {
            perror("Error in sending data packets");
            exit(EXIT_FAILURE);
        }
        byteSent += n;
    }
}