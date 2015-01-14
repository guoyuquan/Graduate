#include<pcap.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netinet/if_ether.h>

/*
 callback function that is passed to pcap_loop(...) and called each time a packet is received
*/
void my_callback(u_char *useless, const struct pcap_hdr* pkthdr, const u_char *packet)
{
    static int count =1;
    fprintf(stdout,"%d ",count);
    if(count==4)
        fprintf(stdout,"come on baby sayyy you love me!!!");
    if(count==7)
        fprintf(stdout,"Tiiimmmeesss!!");
    fflush(stdout);
    count++;
}

int main(int argc, char **argv)
{
    int i;
    char *dev;
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* descr;
    const u_char *packet;
    struct pcap_pkthdr hdr;//pcap.h
    struct ether_header *eptr;//net/ethernet.h
    if(argc!=2)
    {
        fprintf(stdout,"Usage:%s numpackets\n", argv[0]);
        return 0;
    }
    /*grab a device peak into...*/
    dev=pcap_lookupdev(errbuf);
    if(dev==NULL)
    {
        printf("%s\n",errbuf);
        exit(1);
    }
    /*open device for reading*/
    descr =pcap_open_live(dev, BUFSIZ, 0, 1000, errbuf);
    if(descr==NULL)
    {
        printf("pcap_open_live(): %s\n", errbuf);
        exit(1);
    }
    /*allright here we call pcap_loop(..)and pass in our callback function*/
    /*int pcap_loop(pcap_t *p, int cnt, pcap_handler callback, u_char *user)*/
    /*if you are wondering what the user argument is all about, so am I*/
    pcap_loop(descr, atoi(argv[1]), my_callback, NULL);
    fprintf(stdout,"\nDone processing, packets... wheew!\n");
    return 0;
}



/*pcap_dispatch() is to collect and process packets. cnt specifies the maximum number of packets to process before returning. A cnt of -1 processes all the packets received in one buffer. A cnt of 0 processes all packets until an error occurs, EOF is reached or the read times out(when doing live reads andd a non-zero read timeout is specified). callback specifies a routine to be called with three arguments: au_char pointer which is passed in from pcap_dispatch(), apointer to the pcap_pkthdr struct(which precede the actual network headers and data), and a u_char pointer to the packet data. The number of packets read is returned.Zero is returned when EOF is reached in a "savefile." A return of -1 indicates an error in which case pcap_perror() or pcap_geterr() may be used to display the error text.
 */


/****************pcap_compile(..)and pcap_setfilter(...)*********************/
/*
 The program consists of one or more primitives.  Primitives usu�
 ally  consist  of  an  id  (name or number) preceded by one or more
 qualifiers.  There are three different kinds of qualifier:
 
 type   qualifiers say what kind of thing  the  id  name  or  number
 refers  to.   Possible  types are host, net and port.  E.g.,
 `host foo', `net 128.3', `port 20'.  If  there  is  no  type
 qualifier, host is assumed.
 
 dir    qualifiers specify a particular transfer direction to and/or
 from id.  Possible directions are src, dst, src or  dst  and
 src  and dst.  E.g., `src foo', `dst net 128.3', `src or dst
 port ftp-data'.  If there is no dir qualifier, src or dst is
 assumed.  For `null' link layers (i.e. point to point proto�
 cols such as slip) the inbound and outbound  qualifiers  can
 be used to specify a desired direction.
 
 proto  qualifiers  restrict  the  match  to  a particular protocol.
 Possible protos are: ether, fddi,  ip,  arp,  rarp,  decnet,
 lat, sca, moprc, mopdl, tcp and udp.  E.g., `ether src foo',
 `arp net 128.3', `tcp port 21'.  If there is no proto quali�
 fier,  all  protocols  consistent with the type are assumed.
 E.g., `src foo' means `(ip or arp or rarp) src foo'  (except
 the latter is not legal syntax), `net bar' means `(ip or arp
 or rarp) net bar' and `port 53' means  `(tcp  or  udp)  port
 53'.
 
 In  addition  to the above, there are some special `primitive' key�
 words that don't follow  the  pattern:  gateway,  broadcast,  less,
 greater  and  arithmetic  expressions.   All of these are described
 below.
 
 More complex filter expressions are built up  by  using  the  words
 and,  or  and  not  to combine primitives.  E.g., `host foo and not
 port ftp and not port ftp-data'.  To save typing, identical  quali�
 fier  lists can be omitted.  E.g., `tcp dst port ftp or ftp-data or
 domain' is exactly the same as `tcp dst port ftp or  tcp  dst  port
 ftp-data or tcp dst port domain'.
 
 Allowable primitives are:
 
 dst host host
 True  if  the  IP  destination  field of the packet is host,
 which may be either an address or a name.
 
 src host host
 True if the IP source field of the packet is host.
 
 host host
 True if either the IP source or destination of the packet is
 host.   Any  of  the above host expressions can be prepended
 with the keywords, ip, arp, or rarp as in:
 ip host host
 which is equivalent to:
 ether proto \ip and host host
 If host is a name with multiple IP addresses,  each  address
 will be checked for a match.
 
 ether dst ehost
 True  if  the  ethernet destination address is ehost.  Ehost
 may be either a name  from  /etc/ethers  or  a  number  (see
 ethers(3N) for numeric format).
 
 ether src ehost
 True if the ethernet source address is ehost.
 
 ether host ehost
 True if either the ethernet source or destination address is
 ehost.
 
 gateway host
 True if the packet used host as a gateway.  I.e., the ether�
 net  source  or destination address was host but neither the
 IP source nor the IP destination was host.  Host must  be  a
 name  and  must be found in both /etc/hosts and /etc/ethers.
 (An equivalent expression is
 ether host ehost and not host host
 which can be used with either names or numbers  for  host  /
 ehost.)
 
 dst net net
 True  if the IP destination address of the packet has a net�
 work number of net. Net may be either a name from  /etc/net�
 works or a network number (see networks(4) for details).
 
 src net net
 True  if  the  IP source address of the packet has a network
 number of net.
 
 net net
 True if either the IP source or destination address  of  the
 packet has a network number of net.
 
 net net mask mask
 True  if  the  IP address matches net with the specific net�
 mask.  May be qualified with src or dst.
 
 net net/len
 True if the IP address matches net a netmask len bits  wide.
 May be qualified with src or dst.
 
 dst port port
 True if the packet is ip/tcp or ip/udp and has a destination
 port value of port.  The port can be a number or a name used
 in  /etc/services  (see  tcp(4P) and udp(4P)).  If a name is
 used, both the port number and protocol are checked.   If  a
 number  or  ambiguous  name is used, only the port number is
 checked (e.g., dst port 513 will print both tcp/login  traf�
 fic  and  udp/who  traffic,  and port domain will print both
 tcp/domain and udp/domain traffic).
 
 src port port
 True if the packet has a source port value of port.
 
 port port
 True if either the source or destination port of the  packet
 is port.  Any of the above port expressions can be prepended
 with the keywords, tcp or udp, as in:
 tcp src port port
 which matches only tcp packets whose source port is port.
 
 less length
 True if the packet has  a  length  less  than  or  equal  to
 length.  This is equivalent to:
 len <= length.
 
 greater length
 True  if  the  packet  has a length greater than or equal to
 length.  This is equivalent to:
 len >= length.
 
 ip proto protocol
 True if the packet is an ip packet (see ip(4P)) of  protocol
 type protocol.  Protocol can be a number or one of the names
 icmp, igrp, udp, nd, or tcp.  Note that the identifiers tcp,
 udp,  and  icmp  are  also  keywords and must be escaped via
 backslash (\), which is \\ in the C-shell.
 
 ether broadcast
 True if the packet is an  ethernet  broadcast  packet.   The
 ether keyword is optional.
 
 ip broadcast
 True if the packet is an IP broadcast packet.  It checks for
 both the all-zeroes and all-ones broadcast conventions,  and
 looks up the local subnet mask.
 
 ether multicast
 True  if  the  packet  is an ethernet multicast packet.  The
 ether keyword is optional.  This is shorthand for  `ether[0]
 & 1 != 0'.
 
 ip multicast
 True if the packet is an IP multicast packet.
 
 ether proto protocol
 True  if the packet is of ether type protocol.  Protocol can
 be a number or a name like ip, arp,  or  rarp.   Note  these
 identifiers  are also keywords and must be escaped via back�
 slash (\).  [In the  case  of  FDDI  (e.g.,  `fddi  protocol
 arp'), the protocol identification comes from the 802.2 Log�
 ical Link Control (LLC) header, which is usually layered  on
 top  of the FDDI header.  Tcpdump assumes, when filtering on
 the protocol identifier, that all FDDI  packets  include  an
 LLC  header,  and  that  the LLC header is in so-called SNAP
 format.]
 
 ip, arp, rarp, decnet
 Abbreviations for:
 ether proto p where p is one of the above protocols.
 
 tcp, udp, icmp
 Abbreviations for:
 ip proto p
 where p is one of the above protocols.
 
 expr relop expr
 True  if the relation holds, where relop is one of >,
 <, >=, <=, =, !=, and expr is an arithmetic
 expression composed  of integer constants (expressed in
 standard C syntax), the nor� mal binary operators [+, -,
 *, /, &, |], a length  operator, and  special  packet
 data accessors.  To access data inside the packet, use the
 following syntax: proto [ expr : size ] Proto is one of
 ether, fddi, ip, arp,  rarp,  tcp,  udp,  or icmp,  and
 indicates the protocol layer for the index opera� tion.
 The byte offset, relative to the  indicated  protocol
 layer, is given by expr.  Size is optional and indicates
 the number of bytes in the field of interest; it can  be
 either one,  two,  or four, and defaults to one.  The
 length opera� tor, indicated by the keyword len, gives the
 length  of  the packet.
 
 For example, `ether[0] & 1 != 0' catches all multicast traf�
 fic.  The expression `ip[0] & 0xf != 5' catches all IP pack�
 ets  with  options.  The  expression  `ip[6:2] & 0x1fff = 0'
 catches only unfragmented datagrams and frag zero  of  frag�
 mented  datagrams.   This check is implicitly applied to the
 tcp and udp index operations.  For instance,  tcp[0]  always
 means  the first byte of the TCP header, and never means the
 first byte of an intervening fragment.
 
 Primitives may be combined using:
 
 A parenthesized group of primitives and operators (parenthe�
 ses are special to the Shell and must be escaped).
 
 Negation (`!' or `not').
 
 Concatenation (`&&' or `and').
 
 Alternation (`||' or `or').
 
 Negation  has  highest  precedence.   Alternation and concatenation
 have equal precedence and  associate  left  to  right.   Note  that
 explicit  and  tokens, not juxtaposition, are now required for con�
 catenation.
 
 If an identifier is given without a keyword, the most  recent  key�
 word is assumed.  For example,
 not host vs and ace
 is short for
 not host vs and host ace
 which should not be confused with
 not ( host vs or ace )
 
 Expression  arguments  can  be passed to tcpdump as either a single
 argument or as multiple arguments, whichever  is  more  convenient.
 Generally,  if  the expression contains Shell metacharacters, it is
 easier to pass it as a single, quoted argument.  Multiple arguments
 are concatenated with spaces before being parsed.
 
 EXAMPLES
 To print all packets arriving at or departing from sundown:
 tcpdump host sundown
 
 To print traffic between helios and either hot or ace:
 tcpdump host helios and \( hot or ace \)
 
 To print all IP packets between ace and any host except helios:
 tcpdump ip host ace and not helios
 
 To print all traffic between local hosts and hosts at Berkeley:
 tcpdump net ucb-ether
 
 To  print  all  ftp  traffic through internet gateway snup: (note that the
 expression is quoted to prevent  the  shell  from  (mis-)interpreting  the
 parentheses):
 tcpdump 'gateway snup and (port ftp or ftp-data)'
 
 To print traffic neither sourced from nor destined for local hosts (if you
 gateway to one other net, this stuff should never make it onto your  local
 net).
 tcpdump ip and not net localnet
 
 To  print  the start and end packets (the SYN and FIN packets) of each TCP
 conversation that involves a non-local host.
 tcpdump 'tcp[13] & 3 != 0 and not src and dst net localnet'
 
 To print IP packets longer than 576 bytes sent through gateway snup:
 tcpdump 'gateway snup and ip[2:2] > 576'
 
 To print IP broadcast or multicast packets that were not sent via ethernet
 broadcast or multicast:
 tcpdump 'ether[0] & 1 = 0 and ip[16] >= 224'
 
 To  print  all  ICMP packets that are not echo requests/replies (i.e., not
 ping packets):
 tcpdump 'icmp[0] != 8 and icmp[0] != 0"

 */







