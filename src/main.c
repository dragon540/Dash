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
#include "page_map.h"

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

    /**temporary config*/
    mapNewURL("/", "../DashServer/resource/index.html");
    mapNewURL("/ex1", "../DashServer/resource/index.html");
    mapNewURL("/new", "../DashServer/resource/example1.html");
    mapNewURL("/dragon", "../DashServer/resource/example1.html");
    mapNewURL("/strawberry", "../DashServer/resource/example1.html");

    //printBSTInorder(rootPtr);
    //printf("%s\n", determineFilepath("/"));

    char url[256];
    readUrlFromGETReq(url, 8080);
    //printf("%s\n", url+1);

    /***char *c;
    c = readFile_dyn("../DashServer/resource/example1.html");
    printf("%s\n", c);
    printf("c : %d\n", strlen(c));***/


    return 0;
}