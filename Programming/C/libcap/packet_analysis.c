#include<pcap.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netinet/if_ether.h>
#include<net/ethernet.h>
#include<netinet/tcp.h>
//#include<netinet/ether.h>

struct my_ip{
u_int8_t	ip_vhl;		/* header length, version */
#define IP_V(ip)	(((ip)->ip_vhl & 0xf0) >> 4)
#define IP_HL(ip)	((ip)->ip_vhl & 0x0f)
u_int8_t	ip_tos;		/* type of service */
u_int16_t	ip_len;		/* total length */
u_int16_t	ip_id;		/* identification */
u_int16_t	ip_off;		/* fragment offset field */
#define	IP_DF 0x4000			/* dont fragment flag */
#define	IP_MF 0x2000			/* more fragments flag */
#define	IP_OFFMASK 0x1fff		/* mask for fragmenting bits */
u_int8_t	ip_ttl;		/* time to live */
u_int8_t	ip_p;		/* protocol */
u_int16_t	ip_sum;		/* checksum */
struct	in_addr ip_src,ip_dst;	/* source and dest address */
};


u_int16_t handle_ethernet(u_char* args, const struct pcap_pkthdr* pkthdr, const u_char* packet)
{
    struct ether_header *eptr;
    eptr=(struct ether_header *) packet;
    
    /*check to see if we have an ip packet*/
    if(ntohs(eptr->ether_type)==ETHERTYPE_IP)
    {
        fprintf(stdout, "ethernet header source: %s", ether_ntoa((const struct ether_addr *)&eptr->ether_shost));
         fprintf(stdout,"\n");
        fprintf(stdout, "destination: %s", ether_ntoa((const struct ether_addr *)&eptr->ether_dhost));
        fprintf(stdout,"(IP)");
         fprintf(stdout,"\n");
    }
    //else if(ntohs(eptr->ether_type)==ETHERTYPE_ARP)
    //{
    //    fprintf(stdout,"(ARP)");
    //}
    //else if(ntohs(eptr->ether_type)==ETHERTYPE_REVARP)
    //{
    //    fprintf(stdout,"(RARP)");
    //}
    //else
    //{
      //  fprintf(stdout,"(?");
        //exit(1);
    //}
   
    return eptr->ether_type;
}

u_char* handle_ip(u_char* args, const struct pcap_pkthdr* pkthdr, const u_char* packet)
{
    const struct my_ip* ip;
    u_int length=pkthdr->len;
    u_int hlen, off, version;
    int i;
    int len;
    /*jump pass the etherent header*/
    ip=(struct my_ip *)(packet+sizeof(struct ether_header));
    struct tcphdr *tcp=(struct tcphdr*)(packet+sizeof(struct ether_header)+sizeof(struct my_ip));
    length -=sizeof(struct ether_header);
    /*check to see we have a pcaket of valid length*/
    if(length<sizeof(struct my_ip))
    {
        printf("truncated ip %d", length);
        return NULL;
    }
    len=ntohs(ip->ip_len);
    hlen=IP_HL(ip); /*header length*/
    version =IP_V(ip);/*ipversion*/
    /*check version*/
    if(version!=4)
    {
        fprintf(stdout,"Unknow version %d\n", version);
        return NULL;
    }
    /*check header length*/
    if(hlen<5)
    {
        fprintf(stdout,"bad-hlen %d\n",hlen);
    }
    /*see if we have as much as packet as we should*/
    if(length<len)
    {
        printf("\ntruncated IP -%d bytes missing\n",len-length);
    }
    /*check to see if we have the first fragment*/
    off=ntohs(ip->ip_off);
    if((off&0x1fff)==0)
    {
        fprintf(stdout,"IP:");
        fprintf(stdout,"%s\n", inet_ntoa(ip->ip_src));
        fprintf(stdout,"%s\n %d %d %d %d\n", inet_ntoa(ip->ip_dst), hlen, version, len, off);
        fprintf(stdout,"%d\n", tcp->th_off);
        fprintf(stdout,"%d\n",ip->ip_p);
    }
    return NULL;
}

void my_callback(u_char *args, const struct pcap_pkthdr* pkthdr, const u_char* packet)
{
    u_int16_t type=handle_ethernet(args, pkthdr, packet);
    if(type==8)
    {
        /*handle IP packet*/
        handle_ip(args, pkthdr, packet);
    }
    else if(type==ETHERTYPE_ARP)
    {
        
    }
    else if(type==ETHERTYPE_REVARP)
    {
        /*handle reverse arp packet*/
    }
}

int main(int argc, char **argv)
{
    char *dev;
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* descr;
    struct bpf_program fp;
    bpf_u_int32 maskp;
    bpf_u_int32 netp;
    u_char * args=NULL;
    
    /*options must be passed in as a string*/
    if(argc<2)
    {
        fprintf(stdout,"Usage: %s numpackets\"options\"\n",argv[0]);
        return 0;
    }
    /*grab a device*/
    dev=pcap_lookupdev(errbuf);
    if(dev==NULL)
    {
        printf("%s\n",errbuf);
        exit(1);
    }
    /*ask pcap for the network address and mask of the device*/
    pcap_lookupnet(dev,&netp,&maskp,errbuf);
    /*open device for reading*/
    descr=pcap_open_live(dev,BUFSIZ, 1, 1000, errbuf);
    if(descr==NULL)
    {
        printf("Pcap_open_live(): %s\n",errbuf);
        exit(1);
    }
    if(argc>2)
    {
        /* try and compile the program*/
        if(pcap_compile(descr, &fp, "ip",1, netp)==-1)
        {
            fprintf(stderr,"Error calling pcap_compile\n");
            exit(1);
        }
        /*set the compilet program as the filter*/
        if(pcap_setfilter(descr,&fp)==-1)
        {
            fprintf(stderr,"Error setting filter\n");
            exit(1);
        }
    }
    /*loop second parameter is how many packets sniffed before return*/
    pcap_loop(descr, atoi(argv[1]),my_callback,args);
    fprintf(stdout,"\nfinished\n");
    return 0;
}
/*something about the ethernet header and address conversion*/

/* This is a name for the 48 bit ethernet address available on many
 systems.  */
/*
struct ether_addr
{
    u_int8_t ether_addr_octet[ETH_ALEN];
} __attribute__ ((__packed__));
 */

/* 10Mb/s ethernet header */
/*
struct ether_header
{
    u_int8_t  ether_dhost[ETH_ALEN];	destination eth addr
    u_int8_t  ether_shost[ETH_ALEN];    source ether addr
    u_int16_t ether_type;		        packet type ID field
} __attribute__ ((__packed__));
*/

/* Convert 48 bit Ethernet ADDRess to ASCII.  */
/*
extern char *ether_ntoa (__const struct ether_addr *__addr) __THROW;
extern char *ether_ntoa_r (__const struct ether_addr *__addr, char *__buf)
__THROW;*/


/* Convert ASCII string S to 48 bit Ethernet address.  */
/*
extern struct ether_addr *ether_aton (__const char *__asc) __THROW;
extern struct ether_addr *ether_aton_r (__const char *__asc,
                                        struct ether_addr *__addr) __THROW;
 extern int ether_hostton (__const char *__hostname, struct ether_addr *__addr)
 __THROW;
 */

