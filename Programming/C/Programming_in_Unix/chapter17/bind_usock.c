#include <sys/socket.h>
#include <sys/un.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int
main()
{
    int fd, size;
    struct sockaddr_un un;
    un.sun_family=AF_UNIX;
    strcpy(un.sun_path, "foo.socket");
    if((fd=socket(AF_UNIX, SOCK_STREAM, 0))<0)
    {
        fprintf(stderr, "socket failed\n");
        exit(0);
    }
    size=offsetof(struct sockaddr_un, sun_path)+strlen(un.sun_path);
    if(bind(fd, (struct sockaddr *)&un, size)<0)
    {
        fprintf(stderr, "bind failed\n");
        exit(0);
    }
    printf("UNIX domain socket bound\n");
    exit(0);
}