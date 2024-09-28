#include "11lab8.h"
//Main
int main(int argc, char *argv[]){

	int c = 0;
	if(argc != 2){
		printf("Invalid number of commands");
		return 0;
	}

	if((fp = fopen(argv[1], "r")) != NULL){
		fseek(fp, 9, SEEK_SET);
		readfile(argv[1]);
	}

	while(1){

	int command, size;
	char name[20];
	printf("\nEnter 1 to add an order,\nEnter 2 to fulfill an order,\nEnter 3 to list the orders\nEnter 4 to specify list,\nEnter 5 to list backwards,\nEnter 6 to count the list,\nEnter 0 to Exit.\n");
	scanf("%d",&command);

	switch(command){
		case 1:
			printf("\nWhat is the name for the order?\n");
			scanf("%s", name);
			printf("\nHow many drinks?\n");
			scanf("%d", &size);
			add(name, size);
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
		case 5:
			backlist(head);
			break;
		case 6:
			count(head, c);
			break;
		case 0:
			savefile(argv[1]);
			freenodes(head);
			return 0;
	}
}
}

//Functions Impletation

int add(char *name, int size){

	NODE *temp;
	temp = (NODE *)malloc(sizeof(NODE));

	if(head==NULL){		//Starts Linked List
		head = temp;
		tail = temp;
		strcpy(temp->name, name);
		temp->size = size;
	}
	else{		
		NODE *p;
		p = head;
		while(p!=NULL){		//Checks for duplicates
			if(strcmp(p->name, name) == 0){
				printf("\nThis name is already taken.\n");
				return 1;
			}
		p = p -> next;
		}
		temp -> next = NULL;	
		tail -> next = temp;
		tail = temp;
		
		strcpy(temp->name, name);
		temp->size = size;
	}
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
	return 1;		
	}

	while(p->next != NULL){	//Removing
		
		if(p==head && p->size <= made){		//head
			printf("%s - %d drinks made\n", p->name, p->size);
			made -= p->size;
			p = p->next;
			free(head);
			head = p;
			continue;
		}
		else if(p->next == tail && p->next->size <= made){	//tail
			printf("%s - %d drinks made\n", p->next->name, p->next->size);
			made -= p->next->size;
			free(p->next);
			tail = p;
			p->next = NULL;
			break;
		}
		else if(p->next->size <= made && p!= tail){		//middle
			printf("%s - %d drinks made\n", p->next->name, p->next->size);
			made -= p->next->size;
			free(p->next);
			p->next = p->next->next;
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

int savefile(char *filename){
	
	NODE *p;
	if((fp = fopen(filename, "w")) == NULL){
		return 1;
	}

	fprintf(fp, "Name\tSize\n");
	p = head;
	while(p != NULL){
		fprintf(fp, "%s\t%d\n", p->name, p->size);
		p = p->next;
	}
	fclose(fp);
	return 1;
}

int readfile(char *filename){

	char name[20];
	int size;
	while(fscanf(fp, "%s%d", name, &size) == 2){
		add(name, size);
	}
		
	return 1;
}

int backlist(NODE *p){

	if(p == tail){
		printf("%s - %d\n", p->name, p->size);
		return;
	}
	else{
		backlist(p->next);
		printf("%s - %d\n", p->name, p->size);
		return;		
	}
}

int count(NODE *p, int counter){

	if(p == tail){
		counter++;
		printf("\n%d orders in list\n", counter);
		return;
	}
	else{
		counter++;	
		count(p->next, counter);
		return;
	}
}

int freenodes(NODE *p){

	if(p == tail){
		free(p);
		return;
	}
	else{
		freenodes(p->next);
		return;
	}
}		












