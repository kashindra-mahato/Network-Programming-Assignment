#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#define MAX 1024
#define SA struct sockaddr



int main(int argc, char const *argv[])
{
	int sockfd, connfd;
	char buff[MAX];
	char msg1[15];
	struct sockaddr_in servaddr, cli;

	// socket create and varification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(argv[2]);
	servaddr.sin_port = htons(atoi(argv[4]));
	

	// connect the client socket to server socket
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");
	
    
   while(1){
	bzero(buff,sizeof(buff));

	// Get input from the user:

    
    // Send the message to server:
    if(send(sockfd, argv[6], strlen(argv[6]),0) < 0){
        printf("Unable to send message\n");
        return -1;
    }
    
    // Receive the server's response:
    if(recv(sockfd,buff, sizeof(buff), 0) < 0){
        printf("Error while receiving server's msg\n");
        return -1;
    }
    
    printf("Server's response: %s\n",buff);
    bzero(buff,sizeof(buff));
    printf("Enter message: ");
    scanf("%s", msg1);
    strcpy(buff,msg1);
    if(strncmp(buff,"again",5)==0){
		send(sockfd, buff, strlen(buff),0);
    }		
    if (strncmp(buff, "quit", 4) == 0) {
		send(sockfd, buff, strlen(buff),0);
		printf("Client Exit...\n");
		break;
    }

   }
 close(sockfd);
}


























