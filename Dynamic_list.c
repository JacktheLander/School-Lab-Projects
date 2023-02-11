/*
 * 
 * 	Lab 5 - Dynamic Lists
 * 	COEN 11 -- Fall 2021
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "11lab4.h"

//Main
counter = 0;

int main(int argc, char *argv[]){ 	
	
	int size;

	if(argc == 2){
		size = atoi(argv[1]);
		printf("The list size is %d\n", size};
	}
	
	struct order{
		int origin;
		union extrainfo extrainfo;
		char name[size]
		int drinks;
	}

	int *tmp = NULL;
	order *ptr = malloc(sizeof(struct order)*size);

	while(1){

	int command;
	printf("\nEnter 1 to add an order,\nEnter 2 to fulfill an order,\nEnter 3 to list the orders\nEnter 4 to specify list,\nEnter 0 to Exit.\n");
	scanf("%d",&command);
	switch(command){
		case 1:
			add(order);
			break;
		case 2:
			fulfill(order);
			break;
		case 3:
			list(order);
			break;
		case 4:
			speclist(order);
			break;
		case 0:
			free(order);
			return 0;
	}
	
}
}

//Functions Impletation

int add(struct order){

	int i;
	int j;
	char nametemp[10];	

	for(i=0;i<10;i++){
		if(order[i].name[0]=='\0'){
			printf("\nWhat is the name for the order?\n");
			scanf("%s",&nametemp);
			for(j=0;j<10;j++){
				if(strcmp(order[j].name, nametemp) == 0){
					printf("\nThis name is already taken.\n");
					return 1;
				}
			}
			strcpy(order[i].name, nametemp);
			printf("\nHow many drinks?\n");
			scanf("%d",&order[i].drinks);
			printf("\nIs this order from 1 Bobadash, or 2 in-store?\n");
			scanf("%d",&order[i].origin);
			if(order[i].origin == 1){
				printf("\nWhat is the phone number?\n");
				scanf("%s",&order[i].extrainfo);
			}
			else if(order[i].origin == 2){
				printf("\nWhat is the order number?\n");
				scanf("%d",&order[i].extrainfo);
			}
			counter++;
			break;
		}
	}
	return 1;

}

int fulfill(struct order){

	int i, j, made;
	printf("\nHow many drinks have been made?\n");
	scanf("%d",&made);
	
	for(i=0;i<10;i++){
		if(order[i].drinks<=made && order[i].name[0]!='\0'){
			printf("%s - %d drinks made\n", order[i].name, order[i].drinks);
			order[i].name[0]='\0';
			made -= order[i].drinks;
			order[i].drinks=0;
			
			for(j=i;j<10;j++){
				int k = j+1;
				order[j] = order[k];
			}
			counter--;
			i--;
			
		}
	}

	printf("\n%d drinks were wasted.\n",made);

	return 1;	
}

int list(struct order){

	int i;
	printf("\nThere are %d orders:\n",counter);
	for(i=0;i<10;i++){
		if(order[i].name[0]!='\0'){
			if(order[i].origin == 1){
				printf("%s - %d drinks, phone #%s\n", order[i].name, order[i].drinks, order[i].extrainfo.phone);
			}
			else if(order[i].origin == 2){
				printf("%s - %d drinks, order #%d\n", order[i].name, order[i].drinks, order[i].extrainfo.ordernum);
			}
		}
	}

	return 1;
}

int speclist(struct order){

	int i, limit;
	printf("\nWhat is the drink limit you want to specify for your list?\n");
	scanf("%d",&limit);

	for(i=0;i<10;i++){
		if(order[i].name[0]!='\0' && order[i].drinks<=limit){
			printf("%s - %d drinks\n", order[i].name, order[i].drinks);
		}
	}

	return 1;
}
















