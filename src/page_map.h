//
// Created by shobhit on 20/4/24.
//

#ifndef DASHSERVER_PAGE_MAP_H
#define DASHSERVER_PAGE_MAP_H

#include <string.h>


/*
 * This file provides functionality to create a mapping between the defined URL(after the website's name) request and
 * the individual web page files hosted on the server.
 */
typedef struct MapBST {
    char MappedURL[256];
    char fileName[256];
    struct MapBST *rightNode;
    struct MapBST *leftNode;
}MapBST;

extern MapBST *rootPtr;

void mapNewURL(char *URL, char *filepath);
void printBSTInorder(MapBST *node);

#endif //DASHSERVER_PAGE_MAP_H
