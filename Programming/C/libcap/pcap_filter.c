#include<pcap.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netinet/if_ether.h>

/* just print a count every time got a packet */

void my_callback(u_char *useless, const struct pcap_pkthdr *pkthdr, const u_char *packet)
{
    static int count=1;
    fprintf(stdout, "%d", count);
    fflush(stdout);
    count++;
}

int main(int argc, char **argv)
{
    int i;
    char *dev;
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *descr;
    struct pcap_pkthdr hdr;
    struct ether_header *eptr;
    struct bpf_program fp; //hold compiled program
    bpf_u_int32 maskp;//subnetmask
    bpf_u_int32 netp;//ip
    
    if(argc!=2)
    {
        fprintf(stdout,"usage:%s\"filter program \" \n", argv[0]);
        return 0;
    }
    /*find a device*/
    dev=pcap_lookupdev(errbuf);
    if(dev==NULL)
    {
        fprintf(stderr,"%s\n",errbuf);
        exit(1);
    }
    /*look up the network address and mask of the device*/
    pcap_lookupnet(dev,&netp,&maskp,errbuf);
    /*open device for reading this time let set it in the promiscuous mode so we are able to monitor traffic to another machine*/
    descr=pcap_open_live(dev,BUFSIZ, 1, 1000, errbuf);
    if(descr==NULL)
    {
        printf("pcap_open_live(): %s\n",errbuf);
        exit(0);
    }
    /*try and compile the program*/
    printf("%d\n",netp);
    
    /*first parameter is the identifier of the device, second is the file pointer to the compiled file, third is the filter rule, fourth is */
    if(pcap_compile(descr, &fp, "ip",1,maskp)==-1)
    {
        fprintf(stderr,"Error calling pcap_compile\n");
        exit(1);
    }
    /*set the compiled program as the filter*/
    if(pcap_setfilter(descr,&fp)==-1)
    {
        fprintf(stderr,"ERROR setting filter\n");
        exit(1);
    }
    /*loop*/
    pcap_loop(descr,-1,my_callback,NULL);
    return 0;
}


