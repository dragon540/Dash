//
// Created by shobhit on 19/2/24.
//

#include "connect.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

// return communication socket_fd on success
// otherwise exits
int estTcpConnection(uint16_t port_num) {
    int connectionSock_fd = socket(AF_INET, SOCK_STREAM, 0);

    // check if connection socket is created successfully or not
    if(connectionSock_fd == -1) {
        perror("Connection socket cannot be established\n");
        exit(EXIT_FAILURE);
    }
    else {
        // on successful connection socket creation// on successful connection socket creation
        int opt = 1;
        int sockopt = setsockopt(connectionSock_fd, SOL_SOCKET, SO_REUSEADDR,
                                 &opt, sizeof(opt));
        // check if socket options are set successfully
        if(sockopt == -1) {
            perror("Connection socket options cannot be set\n");
            exit(EXIT_FAILURE);
        }
        else {
            // bind the connection socket to appropriate port
            struct sockaddr_in connectionAddr;
            connectionAddr.sin_family = AF_INET;
            connectionAddr.sin_addr.s_addr = htonl(INADDR_ANY);
            connectionAddr.sin_port = htons(port_num);
            connectionAddr.sin_zero[8] = '\0';

            int success = bind(connectionSock_fd, (struct sockaddr*)&connectionAddr,
                    sizeof(struct sockaddr));

            // check if bind is done successfully
            if(success == -1) {
                perror("Cannot bind socket to the correct port\n");
                exit(EXIT_FAILURE);
            }
            else {
                int status = listen(connectionSock_fd, 16);
                if(status == -1) {
                    perror("Cannot listen to any connection\n");
                    exit(EXIT_FAILURE);
                }
                else {
                    struct sockaddr_storage storage_sockAddr;
                    socklen_t storage_sockAddr_size = sizeof(storage_sockAddr);

                    int communicateSock_fd = accept(connectionSock_fd, (struct sockaddr*)&storage_sockAddr,
                            &storage_sockAddr_size);

                    if(communicateSock_fd == -1) {
                        perror("Cannot establish connection\n");
                        exit(EXIT_FAILURE);
                    }
                    else {
                        printf("TCP connection established\n");
                        return communicateSock_fd;
                    }
                }
            }
        }
    }
}
