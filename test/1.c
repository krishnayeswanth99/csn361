// UDP server 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> 


#define sendrecvflag 0 
#define nofile "File Not Found!" 

// function to clear buffer 
void clearBuf(char* b) 
{ 
	int i; 
	for (i = 0; i < 32; i++) 
		b[i] = '\0'; 
} 

// function sending file 
int sendFile(FILE* fp, char* buf, int s) 
{ 
	int i, len; 
	if (fp == NULL) { 
		strcpy(buf, nofile); 
		len = strlen(nofile); 
		buf[len] = EOF; 
		return 1; 
	} 

	char ch; 
	for (i = 0; i < s; i++) { 
		ch = fgetc(fp);
		buf[i] = ch; 
		if (ch == EOF) 
			return 1; 
	} 
	return 0; 
} 

int main() 
{ 
	int fd, nBytes; 
	struct sockaddr_in addr_con; 
	int addrlen = sizeof(addr_con); 
	addr_con.sin_family = AF_INET; 
	addr_con.sin_port = htons(8080); 
	addr_con.sin_addr.s_addr = INADDR_ANY; 
	char buf[32]; 
	FILE* fp; 

	// socket define
	fd = socket(AF_INET, SOCK_DGRAM, 0); 

	if (fd < 0){
        printf("Socket define failed\n");
        exit(0);
    }  

	// binding socket 
	if (bind(fd, (struct sockaddr*)&addr_con, sizeof(addr_con)) != 0){
        printf("Binding Failed!\n");
        exit(0);
    }

	while (1) { 
		printf("Waiting for file name...\n"); 

		// clearing buffer 
		clearBuf(buf); 

		recvfrom(fd, buf, 32, sendrecvflag, (struct sockaddr*)&addr_con, &addrlen); 

		fp = fopen(buf, "r"); 
		printf("File Name Received: %s\n", buf);

		while (1) { 

			// process 
			if (sendFile(fp, buf, 32)) { 
				sendto(fd, buf, 32, sendrecvflag, (struct sockaddr*)&addr_con, addrlen); 
				break; 
			} 

			// send 
			sendto(fd, buf, 32, sendrecvflag, (struct sockaddr*)&addr_con, addrlen); 
			clearBuf(buf); 
		} 
		if (fp != NULL) 
			fclose(fp); 
	} 
	return 0; 
} 
