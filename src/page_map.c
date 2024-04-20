//
// Created by shobhit on 20/4/24.
//
#include "page_map.h"

#include <string.h>
#include <stdlib.h>

void mapNewURL(char URL[256], char filepath[256]) {
    if(rootPtr == NULL) {
        rootPtr = (MapBST*) malloc(sizeof(MapBST));
        strcpy(rootPtr->MappedURL, URL);
        strcpy(rootPtr->fileName, filepath);
        rootPtr->rightNode = NULL;
        rootPtr->leftNode = NULL;
    }
    else {
        MapBST *temp = rootPtr;
        while(temp != NULL) {
            // value of the URL to be mapped is lexicographically smaller than value of current node
            if(strcmp(temp->MappedURL, URL) < 0) {
                temp = temp->leftNode;
            }
            // value of the URL to be mapped is lexicographically larger than value of current node
            else if(strcmp(temp->MappedURL, URL) > 0) {
                temp = temp->rightNode;
            }
        }
        temp = (MapBST*) malloc(sizeof(MapBST));
        strcpy(temp->MappedURL, URL);
        strcpy(temp->fileName, filepath);
        temp->leftNode = NULL;
        temp->rightNode = NULL;
    }
}