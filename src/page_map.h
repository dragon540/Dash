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

// prints BST in inorder for testing
void printBSTInorder(MapBST *node);

// maps URL string to the filepath string
void mapNewURL(char *URL, char *filepath);

// takes URL as parameter and returns the filepath mapped to that particular URL
// NOTE: if no mapping is found then returns the filepath mapped to the rootPtr of the MapBST
char* determineFilepath(char *URL);

#endif //DASHSERVER_PAGE_MAP_H
