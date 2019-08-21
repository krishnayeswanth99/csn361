#include<stdio.h>
#include<sys/socket.h>
#include<netdb.h>

int main(int argc, char* argv[]){

    if(argc != 2){
        printf("Usage Error");
        return -1;
    }

    struct hostent *he;
    struct in_addr ipV4;
    inet_pton(AF_INET,argv[1],&ipV4);
    he = gethostbyaddr(&ipV4,sizeof ipV4,AF_INET);

    printf("Host: %s\n",he->h_name);
    return 0;
}