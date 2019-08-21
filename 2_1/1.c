#include<stdio.h>
#include<stdbool.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(){
    struct sockaddr_in ser,cli;
    int len = sizeof(cli);
    char buff[256];

    int fd = socket(AF_INET,SOCK_STREAM,0),sock;
    if(fd == -1){
        printf("Could not create socket\n");
        return 0;
    }
    int port;
    printf("Port: ");
    scanf("%d",&port);
    printf("\n");
    ser.sin_addr.s_addr = INADDR_ANY;
    ser.sin_family = AF_INET;
    ser.sin_port = htons(port);

    if(bind(fd,&ser,sizeof(ser))){
        printf("Bind failed");
        return 0;
    }

    listen(fd,1);
    sock=accept(fd,&cli,(socklen_t*)&len);
    if(sock){
        printf("Error connecting");
        return 0;
    }
    bool b=1;int i;
    printf("Choose what to do:\n");
    printf("1.Send message\n");
    printf("2.Recieve message\n");
    printf("3.Disconnect\n");
    while(b && sock){
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