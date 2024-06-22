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

    sendAppropriateResponse_200OK(GET,80);

    return 0;
}