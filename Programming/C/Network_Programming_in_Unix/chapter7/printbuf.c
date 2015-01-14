#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int sock=socket(AF_INET, SOCK_STREAM, 0);
    int size;
    socklen_t len=sizeof(size);
    getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void *) &size, &len);
    printf("TCP receive buf:%d\n", size);
    getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void *)&size, &len);
    printf("TCP send buf: %d\n", size);
    //close(sock);
    sock=socket(AF_INET, SOCK_DGRAM, 0);
    getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void *) &size, &len);
    printf("UDP receive buf:%d\n", size);
    getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void *)&size, &len);
    printf("UDP send buf: %d\n", size);
    //close(sock);
    sock=socket(AF_INET, SOCK_SEQPACKET, 0);
    getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void *) &size, &len);
    printf("TCP receive buf:%d\n", size);
    getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void *)&size, &len);
    printf("TCP send buf: %d\n", size);
    return 0;
}