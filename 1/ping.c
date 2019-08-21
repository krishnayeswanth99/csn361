#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/ip_icmp.h>
#include<time.h>
#include<fcntl.h>
#include<signal.h>

#define PING_PKT_SIZ 64

int pingloop = 1;

struct ping_pkt{
    struct icmphdr hdr;
    char msg[PING_PKT_SIZ-sizeof(struct icmphdr)];
};

unsigned short checksum(void *b, int len){
    unsigned short *buf = b;
    unsigned int sum = 0;
    unsigned short result;

    for(sum=0;len>1;len=-2)
        sum += *buf++;
    if(len == 1)
        sum += *(unsigned char*)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum>>16);
    result = ~sum;
    return result;
}
void intHandler(int dummy){
    pingloop = 0;
}

char *dns_lookup(char *addr_host, struct sockaddr_in *addr_con){
    printf("\nResolving DNS..\n");
    struct hostent *host_entity;
    char *ip = (char*)malloc(NI_MAX)
}
void send_ping(int ping_sockfd, struct sockaddr_in *ping_addr, char *ping_dom, char *ping_ip, char *rev_host){
    int ttl_val=64, msg_count=0,i,addr_len,flag=1,msg_recv_count=0;


}