//
// Created by shobhit on 17/2/24.
//

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "connect.h"
#include "communicate.h"
#include "read_resource.h"
#include "helper.h"

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
    readUrlFromGETReq(url, 80);
    //printf("%s\n", url);
    /***char *c;
    c = readFile_dyn("/home/shobhit/Desktop/temp");
    printf("%s\n", c);
    printf("c : %d\n", strlen(c));***/


    return 0;
}