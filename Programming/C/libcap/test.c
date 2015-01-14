#include <stdio.h>
#include <pcap/pcap.h>
int main(int argc,char *argv[]) {
    char *dev,errbuf[PCAP_ERRBUF_SIZE];
    dev=pcap_lookupdev(errbuf);
    if(dev==NULL) {
        printf("couldn't find default device: %s\n",errbuf);
        return(2);
    }
    printf("Device: %s\n",dev);
    return(0);
}