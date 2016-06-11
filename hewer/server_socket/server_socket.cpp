#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstdio>
//#include <stdio.h>
//#include <errno.h>
//#include <string.h>
//#include <sys/types.h>
#include <iostream>
#include "server_socket.hpp"



ServerSocket::ServerSocket(int port, int host)
{
    int creation_exit = create_socket(AF_INET, SOCK_STREAM, 0);

    if(creation_exit < 0){
       std::cout << "Creation of socket failed: " << creation_exit << "\n" << std::endl;
       exit(1);
    } else{
       std::cout << "Creation exit arg: " << creation_exit << "\n" << std::endl;
    };

    prepare_host_address(AF_INET, host, port);
    std::cout << serv_addr.sin_family << " " << serv_addr.sin_addr.s_addr << " " << serv_addr.sin_port << "\n";

    struct sockaddr * temp = (struct sockaddr*)&serv_addr; //casting on pointers
    int binding_exit = bind_socket(listenfd, temp, sizeof(serv_addr));

    if(binding_exit < 0){
       std::cout << "Binding of socket failed: " << binding_exit << "\n" << std::endl;
       exit(1);
    } else{
       std::cout << "Binding exit arg: " << creation_exit << "\n" << std::endl;
    };
};

ServerSocket::~ServerSocket(){
    std::cout << "Closing socket." <<  "\n" << std::endl;
    close(listenfd);
};

int ServerSocket::create_socket(int domain, int type, int protocol)
{
        listenfd = socket(domain, type, protocol);
        return listenfd;
};

int ServerSocket::bind_socket(int fd, struct sockaddr *local_addr, socklen_t addr_length)
{
        return bind(fd, local_addr, addr_length);
};

void ServerSocket::prepare_host_address(int family, int host, int port)
{
    serv_addr.sin_family = family;
    serv_addr.sin_addr.s_addr = host;
    serv_addr.sin_port = htons(port);
};

void ServerSocket::listen_socket(int connections)
{
    listen(listenfd, connections);
};

int ServerSocket::accept_socket(struct sockaddr *client_addr, socklen_t client_length){
    return accept(listenfd, client_addr, &client_length);
};

void ServerSocket::run_socket(void){
    listen_socket(10);

    while(1){
        connfd = accept_socket((struct sockaddr*)&client_addr, sizeof(client_addr)); //casting on pointers
        std::cout << "Accepted connection status: " << connfd << "\n";
        if(connfd < 0){
           exit(1);
        };
        printf("IP address is: %s\n", inet_ntoa(client_addr.sin_addr));
        printf("port is: %d\n", (int) ntohs(client_addr.sin_port));

    };
};
