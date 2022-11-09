#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>


#define MSGLEN 1024

struct sockaddr_in get_socket_addr_in(size_t port) {
    struct sockaddr_in si = { 0 };
    si.sin_family = AF_INET;
    si.sin_addr.s_addr = htonl(0x7f000001);
    si.sin_port = htons((uint16_t) port);

    return si;
}


int main(int argc, char *argv[]) {
    // struct sockaddr_in si = {0};
    struct sockaddr_in si = get_socket_addr_in(1337);
    struct sockaddr client = {0};

    socklen_t c_size = sizeof(client);

    // si.sin_family = AF_INET;
    // si.sin_port = htons(1337);


    int sfd = socket(AF_INET, SOCK_STREAM, 0);


    setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));

    if(0 > sfd) { return -1; }

    if(0 > connect(sfd, (struct sockaddr*) &si, (socklen_t) sizeof(si))) { return -1; }




    char msg[MSGLEN];

    recv(sfd, msg, MSGLEN, 0);

    printf("%s", msg);

    close(sfd);

    return 0;
}