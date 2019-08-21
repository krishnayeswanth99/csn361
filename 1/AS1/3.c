#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip_icmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h> 

char *dns_lookup(char *addr_host, struct sockaddr_in *addr_con) 
{ 
    printf("\nResolving DNS..\n"); 
    struct hostent *host_entity; 
    char *ip=(char*)malloc(NI_MAXHOST*sizeof(char)); 
    int i; 
  
    if ((host_entity = gethostbyname(addr_host)) == NULL) 
    {  
        return NULL; 
    } 
      
    strcpy(ip, inet_ntoa(*(struct in_addr *) 
                          host_entity->h_addr)); 
  
    (*addr_con).sin_family = host_entity->h_addrtype; 
    (*addr_con).sin_port = htons (0); 
    (*addr_con).sin_addr.s_addr  = *(long*)host_entity->h_addr; 
  
    return ip; 
      
} 
  
int main(int argc, char *argv[]) {

    int sockfd; 
    char *ip_addr, *reverse_hostname; 
    struct sockaddr_in addr_con; 
  
    if(argc!=2) 
    { 
        printf("\nIncorrect Format %s <address>\n", argv[0]); 
        return 0; 
    } 
  
    ip_addr = dns_lookup(argv[1], &addr_con); 

    printf("\nPING '%s' IP: %s\n", argv[1], ip_addr); 
 
    int s = socket(PF_INET, SOCK_RAW, 1);

    if(s <= 0)
    {
        perror("Socket Error");
        exit(0);
    }

    typedef struct {
        uint8_t type;
        uint8_t code;
        uint16_t chksum;
        uint32_t data;
    } icmp_hdr_t;

    icmp_hdr_t pckt;

    pckt.type = ICMP_ECHO;          
    pckt.code = 0;          
    pckt.chksum = 0xfff7;   
    pckt.data = 0;        

    printf("%d\n", sizeof(pckt));
    
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = 0;
    addr.sin_addr.s_addr = inet_addr("172.217.167.46");

    int actionSendResult = sendto(s, &pckt, sizeof(pckt),
                                  0, (struct sockaddr*)&addr, sizeof(addr));

    if(actionSendResult < 0)
    {
        perror("Ping Error");
        exit(0);
    }

    unsigned int resAddressSize;
    unsigned char res[30] = "";
    struct sockaddr resAddress;

    int ressponse = recvfrom(s, res, sizeof(res), 0, &resAddress,
                             &resAddressSize);
    if( ressponse > 0)
    {
        // 64 bytes from del03s16-in-f14.1e100.net (172.217.167.46): icmp_seq=3 ttl=50 time=46.1 ms
        printf("%d bytes from %s : %s\n", ressponse, ip_addr, argv[1]);


        exit(0);
    }
    else
    {
        perror("Response Error");
        exit(0);
    }

    return 0;
}
