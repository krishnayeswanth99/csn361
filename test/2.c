// UDP client
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> 
  
#define flag 0 

// function to clear buffer 
void clearBuf(char* b) 
{ 
	int i; 
	for (i = 0; i < 32; i++) 
		b[i] = '\0'; 
} 


// function to receive file 
int recvFile(char* buf, int s) 
{ 
	int i; 
	char ch; 
	for (i = 0; i < s; i++) { 
		ch = buf[i];
		if (ch == EOF) 
			return 1; 
		else
			printf("%c", ch); 
	} 
	return 0; 
} 

 
int main(int argc,char* argv[]) 
{ 
	int fd, nBytes; 
	struct sockaddr_in addr_con; 
	int len = sizeof(addr_con); 
	addr_con.sin_family = AF_INET; 
	addr_con.sin_port = htons(8080); 
	addr_con.sin_addr.s_addr = inet_addr(argv[1]); 
	char net_buf[32]; 
	FILE* fp; 

	// socket define 
	fd = socket(AF_INET, SOCK_DGRAM, 0); 

	if (fd < 0){
        printf("Socket not available\n");
        exit(0);
    }  
	while (1) { 
		printf("\nPlease enter file name to receive:\n"); 
		scanf("%s", net_buf); 
		sendto(fd, net_buf, 32, 
			flag, (struct sockaddr*)&addr_con, 
			len); 

		printf("\n---------File Received---------\n"); 

		while (1) { 
			// receive 
			clearBuf(net_buf); 
			recvfrom(fd, net_buf, 32, flag, (struct sockaddr*)&addr_con, &len); 

			// process 
			if (recvFile(net_buf, 32)) { 
				break; 
			} 
		} 
		printf("\n-------------------------------\n"); 
	} 
	return 0; 
} 
