#include <stdio.h>
#include <stdlib.h>

//Global Variables

int counter = 0;
struct order{
	char name[10];
	int drinks;
};

struct order order[10];

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
			counter++;
			break;
		}
	}
	return 1;

}

int fulfill(){

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
				strcpy(order[j].name, order[k].name);
				order[j].drinks = order[k].drinks;
			}
			counter--;
			
		}
	}

	printf("\n%d drinks were wasted.\n",made);

	return 1;	
}

int list(){

	int i;
	printf("\nThere are %d orders:\n",counter);
	for(i=0;i<10;i++){
		if(order[i].name[0]!='\0'){
			printf("%s - %d drinks\n", order[i].name, order[i].drinks);
		}
	}

	return 1;
}

int speclist(){

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
















