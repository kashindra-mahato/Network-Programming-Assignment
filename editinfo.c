#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include "linkedlist.c"
int main()
{
    head = NULL;
    int choice;
    int id;
    char name[40];
    char reg_no[15];
    printf("1 to insert student details\n2 to search for student details\n3 display\n4 to write linked list \n5 read data");
    do
    {
        printf("\nEnter Choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                printf("Enter id: ");
                scanf("%d", &id);
                printf("Enter name: ");
                scanf("%s", &name);
                printf("Enter registration number: ");
                scanf("%s", &reg_no);
                insert(id, name, reg_no);
                break;
            case 2:
                printf("Enter registration number to search: ");
                scanf("%s", &reg_no);
                search(reg_no);
                break;
	    case 3:
                display();
                break;
	    case 4:
                writeData(head);
                break;
	    case 5:
		readData(head);
		break;
           
        }
        
    } while (choice != 0);
}
