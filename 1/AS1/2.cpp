#include<sys/ioctl.h>
#include<net/if.h>
#include<netinet/in.h>
#include<iostream>
#include<arpa/inet.h>
#include<string.h>

int main(){
    char buf[1024];
    struct ifconf ifc;
    struct ifreq* ifr;
    int sock;
    int nInterfaces;
    unsigned char *mac;

    sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock < 0){
        perror("socket");
        return -1;
    }

    ifc.ifc_len = sizeof(buf);
    ifc.ifc_buf = buf;
    if(ioctl(sock,SIOCGIFCONF,&ifc) < 0){
        perror("SIOCGIFCONF");
        return -1;
    }

    ifr = ifc.ifc_req;
    nInterfaces = ifc.ifc_len / sizeof(struct ifreq);
    for(int i = 0;i<nInterfaces;i++){
        struct ifreq *item = &ifr[i];
        if(strcmp(item->ifr_name,"lo")){

        printf("%s: IP %s",item->ifr_name,inet_ntoa(((struct sockaddr_in *)&item->ifr_addr)->sin_addr));
        printf(", MAC: ");
        struct ifreq temp;
        strcpy(temp.ifr_name,item->ifr_name);
        if(ioctl(sock,SIOCGIFHWADDR,&temp) < 0){
            perror("ioctl");
        }
        unsigned char* hwaddr = (unsigned char*)temp.ifr_hwaddr.sa_data;
        printf("%02X:%02X:%02X:%02X:%02X:%02X\n", hwaddr[0], hwaddr[1], hwaddr[2],
                                          hwaddr[3], hwaddr[4], hwaddr[5]);

        if(ioctl(sock,SIOCGIFBRDADDR,item) >= 0){
            printf(", BROADCAST %s",inet_ntoa(((struct sockaddr_in *)&item->ifr_broadaddr)->sin_addr));
        }
        printf("\n");
        }
    }
    return 0;
}