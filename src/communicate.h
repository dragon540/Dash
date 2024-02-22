//
// Created by shobhit on 19/2/24.
//

#ifndef DASHSERVER_COMMUNICATE_H
#define DASHSERVER_COMMUNICATE_H

#include <stdint.h>

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

#endif //DASHSERVER_COMMUNICATE_H
