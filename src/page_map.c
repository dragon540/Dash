//
// Created by shobhit on 20/4/24.
//
#include "page_map.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

MapBST *rootPtr = NULL;

// prints BST in inorder for testing
void printBSTInorder(MapBST *node) {
    if(node == NULL) {
        printf("Empty tree\n");
    }
    else {
        printf("URL : %s\nFilename : %s\n\n", node->MappedURL, node->fileName);
        printBSTInorder(node->leftNode);
        printBSTInorder(node->rightNode);
    }
}

// maps URL string to the filepath string
void mapNewURL(char *URL, char *filepath) {
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
            if(strcmp(URL, temp->fileName) < 0) {
                if(temp->leftNode != NULL)
                    temp = temp->leftNode;
                else {
                    temp->leftNode = (MapBST*) malloc(sizeof(MapBST));
                    temp = temp->leftNode;
                    break;
                }
            }
            // value of the URL to be mapped is lexicographically larger than value of current node
            else if(strcmp(URL, temp->fileName) > 0) {
                if(temp->rightNode != NULL)
                    temp = temp->rightNode;
                else {
                    temp->rightNode = (MapBST*) malloc(sizeof(MapBST));
                    temp = temp->rightNode;
                    break;
                }
            }
        }
        strcpy(temp->MappedURL, URL);
        strcpy(temp->fileName, filepath);
        temp->leftNode = NULL;
        temp->rightNode = NULL;
    }
}

// takes URL as parameter and returns the filepath mapped to that particular URL
// NOTE: if no mapping is found then returns NULL pointer
char* determineFilepath(char *URL) {
    MapBST *temp = rootPtr;
    while(temp != NULL) {
        if(strcmp(URL, temp->MappedURL) == 0) {
            return temp->fileName;
        }
        else if(strcmp(URL, temp->MappedURL) > 0) {
            if(temp->rightNode != NULL)
                temp = temp->rightNode;
            else
                //return rootPtr->fileName;
                return NULL;
        }
        else if(strcmp(URL, temp->MappedURL) < 0) {
            if(temp->leftNode != NULL)
                temp = temp->leftNode;
            else
                //return rootPtr->fileName;
                return NULL;
        }
    }
}