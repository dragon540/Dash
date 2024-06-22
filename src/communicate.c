//
// Created by shobhit on 19/2/24.
//

#include "communicate.h"
#include "connect.h"
#include "read_resource.h"
#include "helper.h"
#include "page_map.h"

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

// assumes the HTTP method is GET
// returns the URL requested in form of an array of character
int readUrlFromGETReq(char *url, uint16_t port_num) {
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
    free(tempBuffer);

    return sock;
    /*** experimental call
    char *filepathToRead = determineFilepath(url);
    char *con = readFile_dyn(filepathToRead);
    printf("%s\n", con);
    char *res = constructOKResponseToSend_dyn(HTML, con);
    sendCompleteResponse(sock, res);
    free(con);
    free(res);
    close(sock);
    end of experimemntal call ***/
}

// 200 OK response depends on whether the type of request was GET, PUT, PUSH
// constructs appropriate 200 OK response based on type of request and sends it
void sendAppropriateResponse_200OK(int reqType, int port_num) {
    if(reqType == GET) {
        char* urlSting[256]; // length = 256 for now, change later
        int sock = readUrlFromGETReq(urlSting, port_num);

        // sending resource
        char *filepathToRead = determineFilepath(urlSting);
        char *con = readFile_dyn(filepathToRead);
        printf("%s\n", con);
        char *res = constructOKResponseToSend_dyn(HTML, con);
        sendCompleteResponse(sock, res);
        free(con);
        free(res);
        close(sock);
    }
    else if(reqType == PUT) {
        reqType = PUT;
    }
    else if(reqType == POST) {
        reqType = POST;
    }
}

// this function creates a valid HTTP/1.1 200 OK response
// free the memory from the caller side
// 200 OK response depends on whether the type of request was GET, PUT, PUSH
// 200 OK response for GET request
char* constructOKResponseToSend_GET_dyn(int conType, char *content) {
    long int respLen = strlen(content);

    char content_length[100] = "Content-Length: ";
    printf("respLen : %ld\n", respLen); // for debugging
    char *num_len = intToStr_dyn(respLen);
    printf("num_len : %s\n", num_len); // for debugging
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

    strcpy(response, response_code);
    strcat(response, content_length);
    strcat(response, content_type);
    strcat(response, content);

    free(num_len);
    return response;
}
// 200 OK response for PUT request
char* constructOKResponseToSend_PUT_dyn(int conType, char *content);
// 200 OK response for PUSH request
char* constructOKResponseToSend_PUSH_dyn(int conType, char *content);