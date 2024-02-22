//
// Created by shobhit on 22/2/24.
//

#include "read_resource.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// assumes a valid filepath is given
// the content of the file is written to char *content
// free() the pointer returned by the function
char* readFile_dyn(char *filepath) {
    FILE *fp = fopen(filepath, "r");
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
