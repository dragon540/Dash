//
// Created by shobhit on 17/2/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "connect.h"

int main(int argc, char *argv[]) {
    printf("Dash server running...\n");

    estTcpConnection(8080);
    return 0;
}