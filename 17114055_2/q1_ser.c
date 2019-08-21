/**
*	@file stdio.h
*	@file stdlib.h
*	@file string.h
*	@file netdb.h
*	@brief this header file contains support values
*	@file netinet/in.h
*	@brief this header file contains inet conversion values
*	@file sys/socket.h
*	@brief this header file contains sockets that are needed
*	to be used for sockets
*	
*	@author   Krishna Yeswanth
*
*	@date 7/31/2019
*/
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h>
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
		bzero(buff, 80); 

		// message from client 
		read(sockfd, buff, sizeof(buff));
		printf("From client: %s\t To client : ", buff); 
		if (strncmp("exit", buff, 4) == 0) { 
			printf("Server Exit...\n"); 
			break; 
		}
		bzero(buff, 80); 
		n = 0; 
		// message into buffer 
		while ((buff[n++] = getchar()) != '\n') 
			; 

		// sending buffer data to client 
		write(sockfd, buff, sizeof(buff)); 

		// if exit end chat  
		if (strncmp("exit", buff, 4) == 0) { 
			printf("Server Exit...\n"); 
			break; 
		} 
	} 
} 
 
int main() 
{ 
	int fd, sock, len,opt=1; 
	struct sockaddr_in ser, cli; 

	// socket creation 
	fd = socket(AF_INET, SOCK_STREAM, 0); 
	if (fd == -1) { 
		printf("socket failed\n"); 
		exit(0); 
	} 
	bzero(&ser, sizeof(ser)); 
	
	if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		printf("setsockopt");
		exit(0);
	}

	// assign IP, PORT 
	ser.sin_family = AF_INET; 
	ser.sin_addr.s_addr = htonl(INADDR_ANY); 
	ser.sin_port = htons(PORT); 

	// Binding socket
	if ((bind(fd, (struct sockaddr*)&ser, sizeof(ser))) != 0) { 
		printf("bind failed\n"); 
		exit(0); 
	}

	// Server listening 
	if ((listen(fd, 5)) != 0) { 
		printf("Listen failed\n"); 
		exit(0); 
	}
	len = sizeof(cli); 

	// Accepting connection 
	sock = accept(fd, (struct sockaddr*)&cli, &len); 
	if (sock < 0) { 
		printf("acccept failed\n"); 
		exit(0); 
	}

	// Chatting function call 
	func(sock); 

	// Closing Socket
	close(sock); 
} 

