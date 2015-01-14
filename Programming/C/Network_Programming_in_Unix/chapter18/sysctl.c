#include <netinet/udp.h>
#include <arpa/inet.h>
#include <netinet/ip_var.h>
#include <netinet/udp_var.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/param.h>

int main()
{
    int mib[4], val;
    size_t len;
    mib[0]=CTL_NET;
    mib[1]=AF_INET;
    mib[2]=IPPROTO_UDP;
    mib[3]=UDPCTL_CHECKSUM;
    
    len=sizeof(val);
    sysctl(mib, 4, &val, &len, NULL, 0);
    printf("udp chechsum flag: %d\n", val);
    return 0;
}