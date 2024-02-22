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

// returns the pointer to a dynamically created string
// containing the first 256 characters
// free the memory from the caller side
char* recvdData_dyn(int communicateSock_fd);

// assumes the HTTP method is GET
// returns the URL requested in form of an array of character
void readUrlFromGETReq(char *url, uint16_t port_num);

void sendOKResponse(int sockfd);

// send() doesn't guarantee to send full data at once
// handles partial sends
// exits on error
void sendCompleteResponse(int sockfd, char *msg);

// HTTP response consists of several parts including METHOD, Content-Length, Content-Type, content
// this function creates a valid HTTP/1.1 200 OK response
// ARGUMENTS - PLAIN or HTML, and a *content which points to the actual message to be sent
// RETURN - pointer to a dynamically allocated string denoting a valid OK response
// free the memory from the caller side
char* constructOKResponseToSend_dyn(int conType, char *content);

#endif //DASHSERVER_COMMUNICATE_H
