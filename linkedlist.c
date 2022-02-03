#include<stdlib.h>
#include<string.h>
#include<stdio.h>

struct Student{
	int id;
	char name[40];
	char reg_no[15];
	int msg_sent_count;
	struct Student *next;
}*head;

void insert(int id, char* name, char* reg_no){
	struct Student *student = (struct Student *) malloc(sizeof(struct Student));
	student -> id = id;
	strcpy(student -> name, name);
	strcpy(student -> reg_no, reg_no);
	student -> next = NULL;

	if(head == NULL){
		head = student;
	}
 	else{
		student -> next = head;
		head = student;
	}
  
}

void search(char* reg_no[15]){
	struct Student *temp = head;
	while(temp!=NULL){
		if(strcmp(temp -> reg_no, reg_no) == 0){
			printf("ID: %d\n", temp->id);
       			printf("Name: %s\n", temp->name);
        		printf("Reg_no: %s\n", temp->reg_no);
			return;
		}
		temp = temp->next;
	}
        printf("Student with reg_no %s not found.\n",temp->reg_no);   
}

void display()
{
    struct Student * temp = head;
    while(temp!=NULL){
        
        printf("ID: %d\n", temp->id);
        printf("Name: %s\n", temp->name);
        printf("Reg_no: %s\n", temp->reg_no);
        temp = temp->next;
        
    }
}
/*
// function to write linked list to a file
void writeLinkedList(char filename[],struct Student* head){
    
    struct Student* temp = head;
    
    FILE* file;
    file = fopen (filename, "w");
    if (file == NULL)
    {
        fprintf(stderr, "\nCouldn't Open File'\n");
        exit (1);
    }
    
    // writing all the nodes of the linked list to the file
    while(temp!=NULL)
    {
        fwrite(temp, sizeof(struct Student), 1, file);
        temp = temp->next;
    }
    
    if(fwrite != 0)
    {
        printf("Linked List stored in the file successfully\n");
    }
       else
    {
           printf("Error While Writing\n");
    }
    
    fclose(file);
    
}

struct Student* readLinkedList(char filename[],char* reg_no[15]){
    
    struct Student* temp = (struct Student *)malloc(sizeof(struct Student));;
    struct Student* head; // points to the first node of the linked list in the file
    struct Student* last; // points to the last node of the linked list in the file
    last = head = NULL;
    
    FILE* file;
    file = fopen (filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "\nCouldn't Open File'\n");
        exit (1);
    }
    
    // reading nodes from the file
    // nodes are read in the same order as they were stored
    // we are using the data stored in the file to create a new linked list
    while(fread(temp, sizeof(struct Student), 1, file))
    {
        
        if(head==NULL)
        {
            head = last = (struct Student *)malloc(sizeof(struct Student));
        }
        else
        {
            last->next = (struct Student *)malloc(sizeof(struct Student));
            last = last->next;
        }
        last->id = temp->id;
        strcpy(last->name, temp->name);
	strcpy(last->reg_no, temp->reg_no);
        last->next = NULL;
      
	struct Student *temp1 = head;
	while(temp!=NULL){
		if(strcmp(temp1 -> reg_no, reg_no) == 0){
			printf("ID: %d\n", temp1->id);
       			printf("Name: %s\n", temp1->name);
        		printf("Reg_no: %s\n", temp1->reg_no);
			return;
		}
		temp1 = temp1->next;
	}
        printf("Student with reg_no %s not found.\n",temp1->reg_no);   
    }
    
    fclose(file);
    
    return head;
    
}

*/


void writeData(struct Student *h){
	FILE *fp = fopen("students","w");

	while(h!=NULL){
		fwrite(h,sizeof(struct Student),1,fp);
		h = h -> next;	
	}
	fclose(fp);
	printf("linked list data is written to the file");
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



























