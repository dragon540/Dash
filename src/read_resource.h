//
// Created by shobhit on 22/2/24.
//

#ifndef DASHSERVER_READ_RESOURCE_H
#define DASHSERVER_READ_RESOURCE_H

#define MAX_LEN_FILELINE 1000 // max characters assumed in a line of the file read

// returns pointer to a dynamically allocated char memory block
// containing the contents of the file to be read
// need to free() the pointer returned by the function after use
char* readFile_dyn(char *filepath);

#endif //DASHSERVER_READ_RESOURCE_H
