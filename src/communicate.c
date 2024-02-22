//
// Created by shobhit on 19/2/24.
//

#include "communicate.h"
#include "connect.h"
#include "read_resource.h"
#include "helper.h"

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
    char *con = readFile_dyn("/home/shobhit/Desktop/temp");
    char *res = constructOKResponseToSend_dyn(PLAIN, con);
    sendCompleteResponse(sock, res);
    free(con);
    free(res);
    /*** end of experimemntal call ***/
}

void sendOKResponse(int sockfd) {
    char *data = "HTTP/1.1 200 OK\nContent-Length: 4\nContent-Type:text/plain\n\npong";
    int len = strlen(data);

    send(sockfd, data, len, 0);
}

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

// this function creates a valid HTTP/1.1 200 OK response
// free the memory from the caller side
char* constructOKResponseToSend_dyn(int conType, char *content) {
    long int respLen = strlen(content);

    char content_length[100] = "Content-Length: ";
    char *num_len = "1100";
    //intToStr_dyn(respLen); -> calling it gives corrupted size vs. prev_size while consolidating error
    strcat(content_length, num_len);
    strcat(content_length, "\n");

    char *content_type;
    switch (conType) {
        case PLAIN:
            content_type = "Content-Type:text/plain\n\n";
            break;
        case HTML:
            content_type = "Content-Type:text/html\n\n";
            break;
    }
    char *response_code = "HTTP/1.1 200 OK\n";
    char *response = (char*) malloc(strlen(response_code) + strlen(content_length) +
            strlen(content_type) + respLen + 1);

    strcat(response, response_code);
    strcat(response, content_length);
    strcat(response, content_type);
    strcat(response, content);
    //strcat(response, "\0");

    return response;
}