//
// Created by shobhit on 17/2/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {
    printf("Dash server running...\n");

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd) {
        //struct sockaddr_in *local_addr = (struct sockaddr_in*) malloc(sizeof(struct sockaddr_in));
        struct sockaddr_in local_addr;
        local_addr.sin_family = AF_INET;
        local_addr.sin_port = htons(8080);
        local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        local_addr.sin_zero[8] = '\0';

        int opt = 1;
        int q = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
        if(q==-1) {
            printf("SOMETHING WENT WRONG\n");
            exit(0);
        }
        else {
            printf("SOMETHING\n");
        }

        int status = bind(sockfd, (struct sockaddr*)&local_addr, (socklen_t)sizeof(struct sockaddr));
        if(status == 0) {
            status = listen(sockfd, 4);
            if(status == 0) {
                struct sockaddr_storage *addrStr;
                socklen_t size_addr = sizeof (*addrStr);
                int n_sockfd = accept(sockfd, (struct sockaddr*)addrStr, &size_addr);
                if(n_sockfd) {
                    printf("Connection established\n");
                }
                else {
                    printf("Connection not established\n");
                }
            }
            else {
                perror("Error\n");
                exit(EXIT_FAILURE);
            }
        }
        else {
            perror("Unable to bind\n");
            exit(EXIT_FAILURE);
        }

    }
    else {
        perror("Error...\n");
        exit(3);
    }
    return 0;
}