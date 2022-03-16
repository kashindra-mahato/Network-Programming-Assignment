#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define MAX 1024
#define SA struct sockaddr

struct Student{
	int id;
	char name[40];
	char reg_no[15];
	int msg_sent_count;
	struct Student *next;
}*head;

void search(char* reg_no[15], int connfd){
	char buff[MAX];
	struct Student *temp = head;
	while(temp!=NULL){
		if(strcmp(temp -> reg_no, reg_no) == 0){
			printf("ID: %d\n", temp->id);
       			printf("Name: %s\n", temp->name);
        		printf("Reg_no: %s\n", temp->reg_no);
			temp->msg_sent_count = temp->msg_sent_count+1;
			printf("msg count: %d\n", temp->msg_sent_count);
			sprintf(buff,"Welcome %s, your unique identification key is %s\nDo you wish to see this information again?\nagain\nquit",temp->name,temp->reg_no);
			if (send(connfd, buff, strlen(buff), 0) < 0){
        			printf("Can't send\n");
        			return -1;
    			}
			return;
		}
		temp = temp->next;
	}
        sprintf(buff,"Student with reg_no %s not found.\n",temp->reg_no);
	if (send(connfd, buff, strlen(buff), 0) < 0){
       	 	printf("Can't send\n");
        	return -1;
       }   
}

void readData(struct Student *h){
	struct Student s1;
	FILE *fp = fopen("students","r");
	while(fread(&s1,sizeof(struct Student),1,fp)){
	  if(h==NULL){
		h = (struct Student*) malloc(sizeof(struct Student));
		h -> id = s1.id;
		strcpy(h->name, s1.name);
		strcpy(h->reg_no, s1.reg_no);
		head = h;
	}else{
		while(h->next != NULL)
			h = h->next;
		h ->next = (struct Student*) malloc(sizeof(struct Student));
		h->next -> id = s1.id;
		strcpy(h->next -> name, s1.name);
		strcpy(h->next -> reg_no, s1.reg_no);
		h->next -> next = NULL;
	     }
	}
	fclose(fp);
}


int main(int argc, char *argv[])
{
    head = NULL;
    char name[40];
    char reg_no[15];
    int msg_sent_count;
    int sockfd, connfd, len;
    char buff[MAX];
    struct sockaddr_in servaddr, cli;

    //load function readData
    readData(head);
    //Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("Could not create socket");
        return 1;
    }
    printf("Socket created\n");

    bzero(&servaddr, sizeof(servaddr));
    
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[2]));
     
    //Bind
    if( bind(sockfd, (SA*)&servaddr, sizeof(servaddr)) < 0)
    {
        //print the error message
        perror("bind failed.");
        return 1;
    }
    printf("bind done\n");
    //Listen
    listen(sockfd, 3);
    //Accept incoming connection
        printf("Waiting for incoming connections...\n");
        len = sizeof(struct sockaddr_in);
        //accept connection from an incoming client
        connfd = accept(sockfd,(struct sockaddr *)&cli,(socklen_t*)&len);
        if (connfd < 0)
        {
            perror("accept failed");
            return 1;
        }
        printf("Connection accepted\n");
   
    while(1){
        bzero(buff,sizeof(buff));

	 if (recv(connfd, buff, sizeof(buff), 0) < 0){
        printf("Couldn't receive\n");
        return -1;
        }
    
    // Respond to client:
    
        if (strncmp(buff, "1", 1) == 0) {
	     search(buff, connfd);
	}
        if(strcmp("again",buff)==0)
        { 
	    if (recv(connfd, buff, sizeof(buff), 0) < 0){
        	printf("Couldn't receive\n");
        	return -1;
            }
            search(buff, connfd);
        }
       
       if (strncmp(buff, "quit", 4) == 0) {
	     
	     printf("Client Exit...\n");
	     break;
	}
        
    }
    close(sockfd);
}
