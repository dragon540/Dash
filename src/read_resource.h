//
// Created by shobhit on 22/2/24.
//

#ifndef DASHSERVER_READ_RESOURCE_H
#define DASHSERVER_READ_RESOURCE_H

// assumes a valid filepath is given
// returns a pointer to the content of the file
// free() the pointer returned by the function
char* readFile_dyn(char *filepath);

#endif //DASHSERVER_READ_RESOURCE_H
