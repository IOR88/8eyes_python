#ifndef CLIENT_SOCKET_H_
#define CLIENT_SOCKET_H_

#include <sys/socket.h>
#include <arpa/inet.h>

class ServerSocket{
    private:
        int listenfd, connfd;
        struct sockaddr_in serv_addr, client_addr;

        int create_socket(int domain, int type, int protocol);
        int bind_socket( int fd, struct sockaddr *local_addr, socklen_t addr_length );
        void prepare_host_address( int family, int host, int port );
    public:
        ServerSocket( int port, int host);
        ~ServerSocket();
        void listen_socket( int connections);
        int accept_socket( struct sockaddr *client_addr, socklen_t client_length );
        void run_socket( void );
};

#endif