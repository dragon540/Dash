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

// returns socket id of the connection and sets
// char *url as url requested in the HTTP request
int readReq(char *url, uint16_t port_num) {
    int sock = estTcpConnection(port_num);
    char *tempBuffer = recvdData_dyn(sock);

    char firstThreeLetter[3];
    for(int i = 0; i < 3; i++) {
        firstThreeLetter[i] = tempBuffer[i];
    }

    if(strcmp(firstThreeLetter, "GET") == 0) {
        readUrlFromGETReq(url, tempBuffer);
        printf("readReq: GET: %s\n", url);
    }
    else if(strcmp(firstThreeLetter, "PUT") == 0) {
        readUrlFromPUTReq(url, tempBuffer);
        printf("readReq: PUT:\n");
    }
    else if(strcmp(firstThreeLetter, "POS") == 0) {
        readUrlFromPOSTReq(url, tempBuffer);
        printf("readReq: POST:\n");
    }
    free(tempBuffer);
    return sock;
}

// assumes the HTTP method is GET
// sets the URL requested in char *url
// char *tempBuffer is the string of complete request
void readUrlFromGETReq(char *url, char *tempBuffer) {
    // example request line
    // GET /index.html HTTP/1.1

    int i = 4;
    while(tempBuffer[i] != '\0' && tempBuffer[i] != ' ') {
        url[i-4] = tempBuffer[i];
        i++;
    }
    url[i-4] = '\0';
}

// assumes the HTTP method is PUT
// sets the URL requested in char *url
// char *tempBuffer is the string of complete request
void readUrlFromPUTReq(char *url, char *tempBuffer) {
    // example request line
    // PUT /index.html HTTP/1.1

    int i = 4;
    while(tempBuffer[i] != '\0' && tempBuffer[i] != ' ') {
        url[i-4] = tempBuffer[i];
        i++;
    }
    url[i-4] = '\0';
    free(tempBuffer);
}

// assumes the HTTP method is POST
// sets the URL requested in char *url
// char *tempBuffer is the string of complete request
void readUrlFromPOSTReq(char *url, char *tempBuffer) {
    // example request line
    // POST /index.html HTTP/1.1

    int i = 5;
    while(tempBuffer[i] != '\0' && tempBuffer[i] != ' ') {
        url[i-5] = tempBuffer[i];
        i++;
    }
    url[i-5] = '\0';
    free(tempBuffer);
}

// 200 OK response depends on whether the type of request was GET, PUT, POST
// constructs appropriate 200 OK response based on type of request and sends it
void sendAppropriateResponse_200OK(int reqType, uint16_t port_num) {
    if(reqType == GET) {
        char urlSting[256]; // length = 256 for now, change later
        int sock = readReq(urlSting, port_num);

        // sending resource
        char *filepathToRead = determineFilepath(urlSting);
        char *con = readFile_dyn(filepathToRead);
        printf("%s\n", con);
        char *res = constructOKResponseToSend_GET_dyn(HTML, con);
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

void sendAppropriateResponse_404NotFound(int reqType, uint16_t port_num) {
    if(reqType == GET) {
        char urlSting[256]; // length = 256 for now, change later
        int sock = readReq(urlSting, port_num);

        // sending resource
        char *filepathToRead = determineFilepath(urlSting);
        //char *con = readFile_dyn(filepathToRead);
        char *con = readFile_dyn("../DashServer/resource/404NotFound.html"); // make it configurable later
        printf("%s\n", con);
        char *res = construct_404NotFound_ResponseToSend_GET_dyn(HTML, con);
        sendCompleteResponse(sock, res);
        free(con);
        free(res);
        close(sock);
    }
}

// this function creates a valid HTTP/1.1 200 OK response
// free the memory from the caller side
// 200 OK response depends on whether the type of request was GET, PUT, POST
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
// 200 OK response for POST request
char* constructOKResponseToSend_POST_dyn(int conType, char *content);

char* construct_404NotFound_ResponseToSend_GET_dyn(int conType, char *content) {
    long int respLen = strlen(content);

    char content_length[100] = "Content-Length: ";
    printf("404 respLen : %ld\n", respLen); // for debugging
    char *num_len = intToStr_dyn(respLen);
    printf("404 num_len : %s\n", num_len); // for debugging
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
    char *response_code = "HTTP/1.1 404 Not Found\n";
    char *response = (char*) malloc(strlen(response_code) + strlen(content_length) +
                                    strlen(content_type) + respLen + 1);

    strcpy(response, response_code);
    strcat(response, content_length);
    strcat(response, content_type);
    strcat(response, content);

    free(num_len);
    return response;
}