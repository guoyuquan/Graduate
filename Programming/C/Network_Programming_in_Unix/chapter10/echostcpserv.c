#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>

#define forever for(;;)

int
main(int argc, char *argv[])
{
    int sock_fd, msg_flags;
    char readbuf[1500];
    struct sockaddr_in servaddr, cliaddr;
    struct sctp_sndrcvinfo sri;
    struct sctp_event_subscribe events;
    int stream_increment=1;
    socklen_t len;
    size_t rd_sz;
    if(argc==2)
    {
        stream_increment=atoi(argv[1]);
    }
    if((sock_fd=socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP))<0)
    {
        fprintf(stderr, "error: create socket: %s\n", strerror(errno));
        exit(0);
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(9868);
    if(bind(sock_fd, (struct sockaddr *)&servaddr, sizeof(servaddr))<0)
    {
        fprintf(stderr, "error, bind(): %s\n", strerror(errno));
        exit(0);
    }
    bzero(&events, sizeof(events));
    events.sctp_data_io_event=1;
    if(setsockopt(sock_fd, IPPROTO_SCTP, SCTP_EVENTS, &events, sizeof(events))<0)
    {
        fprintf(stderr, "error, setsockopt: %s\n", strerror(errno));
        exit(0);
    }
    if(listen(sock_fd, 5)<0)
    {
        fprintf(stderr, "error, listen(): %s\n", strerror(errno));
        exit(0);
    }
    forever
    {
        len=sizeof(struct sockaddr_in);
        rd_sz=sctp_recvmsg(sock_fd, readbuf, sizeof(readbuf), (struct sockaddr*)&cliaddr, &len, &sri, &msg_flags);
        if(stream_increment)
        {
            sri.sinfo_stream++;
            if(sri.sinfo_stream>=sctp_get_no_strms(sock_fd, (struct sockaddr*)&cliaddr, len))
                sri.sinfo_stream=0;
        }
        if(sctp_sendmsg(sock_fd, readbuf, rd_sz, (struct sockaddr *)&cliaddr, len, sri.sinfo_ppid, sri.info_flags, sri.sinfo_stream, 0, 0);
    }
}


