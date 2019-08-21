#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

void func(int fd){
    char buff[80];
    int n;
    for(;;){
        bzero(buff,80);
        n=0;
        while((buff[n++]=getchar())!='\n');

        write(fd,buff,sizeof(buff));
        bzero(buff,sizeof(buff));
        read(fd,buff,sizeof(buff));
        printf("From Server: %s",buff);
        if((strncmp(buff,"exit",4))==0){
            printf("Client Exit...\n");
            break;
        }
    }
}
int main(int argc,char* argv[]){
    if(argc!=3){
        printf("Usage: file ip port");
        exit(0);
    }
    int fd;
    struct sockaddr_in cli;
    socklen_t l=sizeof(cli);

    fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd==-1){
        printf("Error");
        exit(0);
    }
    cli.sin_family=AF_INET;
    cli.sin_addr.s_addr=htonl(argv[1]);
    cli.sin_port=htons(argv[2]);

    if(connect(fd,(struct sockaddr*)&cli,&l)!=0){
        printf("connect failed");
        exit(0);
    }
    func(fd);
    close(fd);
}