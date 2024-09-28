#include <stdio.h>
#include <stdlib.h>
#define NODE struct node
#include <string.h>

//Global Variables
struct node{
	char name[20];
	int size;
	NODE *next;
};

NODE *head = NULL;
NODE *tail = NULL;

int counter = 0;

//Functions Declared

int add();
int fulfill();
int list();
int speclist();

//Main

int main(){
	
	while(1){
	int command;
	printf("\nEnter 1 to add an order,\nEnter 2 to fulfill an order,\nEnter 3 to list the orders\nEnter 4 to specify list,\nEnter 0 to Exit.\n");
	scanf("%d",&command);

	switch(command){
		case 1:
			add();
			break;
		case 2:
			fulfill();
			break;
		case 3:
			list();
			break;
		case 4:
			speclist();
			break;
		case 0:
			return 0;
	}
}
}

//Functions Impletation

int add(){

	NODE *temp;
	temp = (NODE *)malloc(sizeof(NODE));

	if(head==NULL){		//Starts Linked List
		head = temp;
		tail = temp;
		printf("\nWhat is the name for the order?\n");
		scanf("%s", &temp->name);
		printf("\nHow many drinks?\n");
		scanf("%d", &temp->size);
	}
	else{	
		temp -> next = NULL;	
		tail -> next = temp;
		tail = temp;
			
		printf("\nWhat is the name for the order?\n");
		scanf("%s", &temp->name);
		NODE *p;
		p = head;
		while(p!=tail){		//Checks for duplicates
			if(strcmp(p->name, temp->name) == 0){
				printf("\nThis name is already taken.\n");
				return 1;
			}
		p = p -> next;
		}
		printf("\nHow many drinks?\n");
		scanf("%d", &temp->size);
	}
	counter++;
	return 1;
}

int fulfill(){
	
	NODE *p;	
	
	int made;
	
	p = head;
	
	if(head == NULL){	//empty
		printf("\nList is empty\n");
		return 1;
	}
	
	printf("\nHow many drinks have been made?\n");
	scanf("%d",&made);
	
	if(head == tail && p->size <= made){		//only one
		printf("%s - %d drinks made\n", p->name, p->size);
		made -= p->size;
		free(head);
		head = NULL;
		tail = NULL;
		counter--;
	return 1;		
	}

	while(p->next != NULL){	//Removing
		
		if(p==head && p->size <= made){		//head
			printf("%s - %d drinks made\n", p->name, p->size);
			made -= p->size;
			p = p->next;
			free(head);
			head = p;
			counter --;
			continue;
		}
		else if(p->next == tail && p->next->size <= made){	//tail
			printf("%s - %d drinks made\n", p->next->name, p->next->size);
			made -= p->next->size;
			free(p->next);
			tail = p;
			p->next = NULL;
			counter --;
			break;
		}
		else if(p->next->size <= made && p!= tail){		//middle
			printf("%s - %d drinks made\n", p->next->name, p->next->size);
			made -= p->next->size;
			free(p->next);
			p->next = p->next->next;
			counter--;
		}
	
	p = p->next;
	}

	printf("\n%d drinks were wasted.\n",made);

	return 1;	
}

int list(){
	
	NODE *p;
	p = head;
	//printf("\nThere are %d orders:\n", counter);
	while(p != NULL){
		
		printf("%s - %d drinks\n", p->name, p->size);
		p = p->next;
	}

	return 1;
}

int speclist(){

	int limit;
	printf("\nWhat is the drink limit you want to specify for your list?\n");
	scanf("%d",&limit);
	
	NODE *p;
	p = head;
	while(p != NULL){
		if(p->size <= limit){
			printf("%s - %d drinks\n", p->name, p->size);
		}
		p = p->next;
	}
	
	return 1;
}
















