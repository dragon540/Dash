//
// Created by shobhit on 19/2/24.
//

#ifndef DASHSERVER_COMMUNICATE_H
#define DASHSERVER_COMMUNICATE_H

#include <stdint.h>

enum Content_Type {
    PLAIN,
    HTML,
};

enum Response_Type {
    GET,
    PUT,
    POST
};

// returns the pointer to a dynamically created string
// containing the first 256 characters
// free the memory from the caller side
char* recvdData_dyn(int communicateSock_fd);

// send() doesn't guarantee to send full data at once
// handles partial sends
// exits on error
void sendCompleteResponse(int sockfd, char *msg);

// assumes the HTTP method is GET
// returns the socket id
// sets the URL requested in form of an array of character
int readUrlFromGETReq(char *url, uint16_t port_num);

// assumes the HTTP method is PUT
// returns the socket id
// sets the URL requested in form of an array of character
int readUrlFromPUTReq(char *url, uint16_t port_num);

// assumes the HTTP method is POST
// returns the socket id
// sets the URL requested in form of an array of character
int readUrlFromPOSTReq(char *url, uint16_t port_num);

// 200 OK response depends on whether the type of request was GET, PUT, PUSH
// constructs appropriate 200 OK response based on type of request and sends it
void sendAppropriateResponse_200OK(int reqType, int port_num);

//void sendAppropriateResponse_404(int reqType, int port_num);

// HTTP response consists of several parts including METHOD, Content-Length, Content-Type, content
// this function creates a valid HTTP/1.1 200 OK response
// ARGUMENTS - PLAIN or HTML, and a *content which points to the actual message to be sent
// RETURN - pointer to a dynamically allocated string denoting a valid OK response
// free the memory from the caller side
// 200 OK response depends on whether the type of request was GET, PUT, PUSH
char* constructOKResponseToSend_GET_dyn(int conType, char *content);
char* constructOKResponseToSend_PUT_dyn(int conType, char *content);
char* constructOKResponseToSend_PUSH_dyn(int conType, char *content);

#endif //DASHSERVER_COMMUNICATE_H
