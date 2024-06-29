//
// Created by shobhit on 17/2/24.
//

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>

#include "connect.h"
#include "communicate.h"
#include "read_resource.h"
#include "helper.h"
#include "page_map.h"
#include "server_config.h"

int main(int argc, char *argv[]) {
    printf("Dash server running...\n");

    URLMappingConfig();

    printBSTInorder(rootPtr);
    //printf("%s\n", determineFilepath("/"));

    int i=0;
    while(1) {

        pthread_t t_id;

        pthread_create(&t_id, NULL, sendResponse, NULL);
        pthread_join(t_id, NULL);
        i++;
        printf("%d\n", i);
    }

    //sendResponse(80);

    return 0;
}