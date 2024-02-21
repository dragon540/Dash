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

    /*** int sock = estTcpConnection(8080);
    printf("%d\n", sock);
    char *str = recvdData_dyn(sock);
    printf("%s\n", str);
    str = recvdData_dyn(sock);
    printf("%s\n", str);
    str = recvdData_dyn(sock);
    printf("%s\n", str);***/

    char url[256];
    readUrlFromGETReq(url);
    printf("%s\n", url);

    return 0;
}