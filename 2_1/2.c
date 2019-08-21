#include<stdio.h>
#include<stdbool.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(int argc,char* argv[]){
    if(argc!=3){
        printf("Wrong Usage\n");
        printf("Usage: host_ip port \n");
        return 0;
    }
    struct sockaddr_in sock;
    char buff[256];

    int fd=socket(AF_INET,SOCK_STREAM,0);
    if(fd==-1){
        printf("Unable to open socket");
        return 0;
    }
    int port = atoi(argv[2]);
    sock.sin_family=AF_INET;
    sock.sin_addr.s_addr=inet_addr(argv[1]);
    sock.sin_port=htons(port);
    if(connect(fd,(struct sockaddr*)&sock,sizeof(sock))){
        printf("Error: Connecting");
        return 0;
    }
    bool b=1;int i;
    printf("Choose what to do:\n");
    printf("1.Send message\n");
    printf("2.Recieve message\n");
    printf("3.Disconnect\n");
    while(b && fd){
        scanf("%d",&i);
        if(i==1){
            printf("\n");
            scanf("%s",buff);
            if(write(sock,buff,strlen(buff))){
                printf("Error: Sending\n");
            }
        }else if(i==2){
            if(read(sock,buff,255)){
                printf("Error: Recieving\n");
            }else
                printf("%s\n",buff);
        }
        else if(i==3)
            b=0;
    }
    return 1;
}