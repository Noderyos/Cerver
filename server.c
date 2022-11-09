#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>


struct sockaddr_in get_socket_addr_in(size_t port) {
    struct sockaddr_in si = { 0 };
    si.sin_family = AF_INET;
    si.sin_port = htons((uint16_t) port);

    return si;
}


int main(int argc, char* argv[]){
    // struct sockaddr_in si = {0};
    struct sockaddr_in si = get_socket_addr_in(1337);
    struct sockaddr client = {0};

    socklen_t c_size = sizeof(client);

    // si.sin_family = AF_INET;
    // si.sin_port = htons(1337);


    int sfd = socket(AF_INET, SOCK_STREAM, 0);


    setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));

    if(0 > sfd) { return -1; }

    if(0 > bind(sfd, (struct sockaddr*) &si, sizeof(si))) { return -1; }
    
    if(0 > listen(sfd, 0)) { return -1; }
    
    int cfd = accept(sfd, &client, &c_size);




    
    char* msg = "hello, world!\n";

    send(cfd, msg, strlen(msg), 0);

    close(cfd);
    close(sfd);

    return 0;
}