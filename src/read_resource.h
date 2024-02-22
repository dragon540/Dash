//
// Created by shobhit on 22/2/24.
//

#ifndef DASHSERVER_READ_RESOURCE_H
#define DASHSERVER_READ_RESOURCE_H

// returns pointer to a dynamically allocated char memory block
// containing the contents of the file to be read
// free() the pointer returned by the function after use
char* readFile_dyn(char *filepath);

#endif //DASHSERVER_READ_RESOURCE_H
