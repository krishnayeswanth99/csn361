#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/ioctl.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<net/if.h>

void func(int sock){
    char buff[80];
    int n;
    for(;;){
        bzero(buff,80);
        read(sock,buff,sizeof(buff));
        printf("From client: %s\n",buff);
        bzero(buff,80);
        n=0;
        while((buff[n++]=getchar())!='\n');

        write(sock,buff,sizeof(buff));

        if(strncmp("exit",buff,4)==0){
            printf("Server exit...\n");
            break;
        }
    }
}
int main(int argc,char* argv[]){
    if(argc!=2){
        printf("Usage: file port\n");
        exit(0);
    }
    struct sockaddr_in ser,cli;
    int fd,sock,len;
    fd=socket(AF_INET,SOCK_STREAM,0);
    if(fd==0){
        printf("Error");
        exit(0);
    }
    
    ser.sin_family=AF_INET;
    ser.sin_port=htons(argv[1]);

    struct ifconf ifc;

    if(inet_pton(AF_INET,INADDR_ANY,&ser.sin_addr)<=0){
        printf("invalid ip/address not found");
        exit(0);
    }

    if(bind(fd,(struct sockaddr*)&ser,sizeof(ser))){
        printf("Bind failed");
        exit(0);
    }
    if(listen(fd,1) < 0){
        printf("Listen failed");
        exit(0);
    }
    len=sizeof(cli);
    sock=accept(fd,(struct sockaddr*)&cli,&len);
    if(sock<0){
        printf("Accept failed");
        exit(0);
    }
    func(sock);
    close(fd);
}