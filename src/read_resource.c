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
// need to free() the pointer returned by the function after use
char* readFile_dyn(char *filepath) {
    FILE *fp = fopen(filepath, "r");
    if(fp == NULL) {
        perror("Can't open file for reading");
        exit(EXIT_FAILURE);
    }
    char curr_line[MAX_LEN_FILELINE];

    // calculate total number of characters in the file
    long file_total_char;
    fseek(fp, 0L, SEEK_END);
    file_total_char = ftell(fp);

    rewind(fp); // sets the file position indicator back to start position

    char *content = (char*) malloc(file_total_char + 1);
    while(fgets(curr_line, MAX_LEN_FILELINE, fp)) {
        strcat(content, curr_line);
    }
    content[file_total_char - 1] = '\0';
    fclose(fp);
    return content;
}
