//
// Created by shobhit on 22/2/24.
//

#include "read_resource.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>

// returns pointer to a dynamically allocated char memory block
// containing the contents of the file to be read
// free() the pointer returned by the function after use
char* readFile_dyn(char *filepath) {
    FILE *fp = fopen(filepath, "r");
    if(fp == NULL) {
        perror("Can't open file for reading");
        exit(EXIT_FAILURE);
    }
    char line[100];
    long l;
    fseek(fp, 0L, SEEK_END);
    l = ftell(fp);
    rewind(fp);
    char *content = (char*) malloc(l);
    while(fgets(line, 100, fp)) {
        strcat(content, line);
    }
    content[l-1] = '\0';
    fclose(fp);
    return content;
}
