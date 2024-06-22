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
#include "server_config.h"

int main(int argc, char *argv[]) {
    printf("Dash server running...\n");

    URLMappingConfig();

    //printBSTInorder(rootPtr);
    //printf("%s\n", determineFilepath("/"));

    char url[256];
    readUrlFromGETReq(url, 80);

    return 0;
}