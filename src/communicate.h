//
// Created by shobhit on 19/2/24.
//

#ifndef DASHSERVER_COMMUNICATE_H
#define DASHSERVER_COMMUNICATE_H

// returns the pointer to a dynamically created string
// containing the first 256 characters
// make sure to free the memory from the caller side
char* recvdData_dyn(int communicateSock_fd);

#endif //DASHSERVER_COMMUNICATE_H
