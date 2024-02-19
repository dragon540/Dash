//
// Created by shobhit on 17/2/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "connect.h"
#include "communicate.h"

int main(int argc, char *argv[]) {
    printf("Dash server running...\n");

    int sock = estTcpConnection(8080);
    printf("%d\n", sock);
    printRecvdData(sock);
    return 0;
}