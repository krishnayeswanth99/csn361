/**
*	@file stdio.h
*	@file stdlib.h
*	@file string.h
*	@file netdb.h
*	@brief this header file contains support values
*	@file sys/socket.h
*	@brief this header file contains sockets that are needed
*	to be used for sockets
*	
*	@author   Krishna Yeswanth
*
*	@date 7/31/2019
*/
#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h>
#define PORT 8080

/**
* This method will be used to chat.
* @author Krishna Yeswanth
* @param sockfd  Socket used for connection
* @date 7/31/2019
*/
void func(int sockfd) 
{ 
	char buff[80]; 
	int n; 
	for (;;) { 
		bzero(buff, sizeof(buff)); 
		printf("Enter the string : "); 
		n = 0; 
		// message into buffer 
		while ((buff[n++] = getchar()) != '\n') 
			; 
		// sending buffer data to server
		write(sockfd, buff, sizeof(buff)); 
		// if exit end chat 
		if ((strncmp(buff, "exit", 4)) == 0) { 
			printf("Client Exit...\n"); 
			break; 
		} 
		bzero(buff, sizeof(buff)); 
		// message from server
		read(sockfd, buff, sizeof(buff)); 
		printf("From Server : %s", buff); 
		// if exit end chat 
		if ((strncmp(buff, "exit", 4)) == 0) { 
			printf("Client Exit...\n"); 
			break; 
		} 
	} 
} 

int main(int argc,char* argv[]) 
{ 
	int sockfd, connfd; 
	struct sockaddr_in ser, cli; 

	// socket creation 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("socket failed\n"); 
		exit(0); 
	} 
	bzero(&ser, sizeof(ser)); 

	// assign IP, PORT 
	ser.sin_family = AF_INET; 
	ser.sin_addr.s_addr = inet_addr(argv[1]); 
	ser.sin_port = htons(PORT); 

	// connecting client to server
	if (connect(sockfd, (struct sockaddr*)&ser, sizeof(ser)) != 0) { 
		printf("connection failed\n"); 
		exit(0); 
	}

	//chatting function
	func(sockfd); 

	// close the socket 
	close(sockfd); 
} 

