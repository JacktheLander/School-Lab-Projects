#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "set.h"	//Header file and libraries
#include <assert.h>
#include <string.h>	

#define EMPTY 0
#define FILLED 1
#define DELETED 2	//Flag definitions

static int search(SET *sp, char *elt, bool *found);	//Hidden search function declaration

typedef struct set{
	char **data;
	int length;
	int count;
	int *flag;
}SET;			//SET structure declaration

//O(1)
unsigned strhash(char *s){	//Hash function for set elements
	unsigned hash = 0;
	while(*s != '\0')
		hash = 31 * hash + *s ++;
	return hash;
}

//O(n)
SET *createSet(int maxElts){	//Create function allocates memory for the set as well as the data and flag arrays within
	SET *sp;
	sp = malloc(sizeof(SET));
	sp->count = 0;
	sp->length = maxElts;
	sp->data = malloc(sizeof(char *)*maxElts);
	sp->flag = malloc(sizeof(char *)*maxElts);
	assert(sp->data != NULL);
	int i;
	for(i=0;i<maxElts;i++){
		sp->flag[i] = 0;	//Flags are initially set to empty
	}
	return sp;
}

//O(n)
static int search(SET *sp, char *elt, bool *found){	//Search function checks the hash of the element and then each of the indexes after
	int idx, i, loc, available;
	available = -1;
	idx = strhash(elt) % sp->length;
	for(i=0; i<sp->length; i++){
		loc=(idx+i) % sp->length;
		if(sp->flag[loc]==0){
			*found = false;
			return loc;
		}
		else if(sp->flag[loc] == 2){
			if(available == -1)
				available = loc;	
		}
		else if(strcmp(sp->data[loc], elt) == 0){
			*found = true;
			return loc;
		}		
	}
	*found = false;
	return -1;
}

//O(n)
void addElement(SET *sp, char *elt){		//Calls the search function to find the first empty index of the hash table for the element
	bool found;
	assert(sp!=NULL && elt!=NULL);
	int loc;
	loc = search(sp, elt, &found);
	if(found == false){
		sp->data[loc]=strdup(elt);	//Copies the element memory into the array, sets the flag to filled, and increments count
		sp->flag[loc]=1;
		sp->count++;
	}
	return;
}

//O(n)
void removeElement(SET *sp, char *elt){		//Calls the search function to find the location of the element
	bool found;
	assert(sp!=NULL && elt!=NULL);
	int loc;
	loc = search(sp, elt, &found);
	if(found == true){		//Sets the flag to deleted, and decrements count
		sp->flag[loc] = 2;
		sp->count --;
		free(sp->data[loc]);
	}
	return;	
}

//O(n)
void destroySet(SET *sp){	//Frees all the elements' pointers in the data array and then the arrays before freeing the set
	assert(sp != NULL);
	int i;
	for(i=0;i<sp->length;i++){
		if(sp->flag[i]==1)
			free(sp->data[i]);
	}
	free(sp->flag);
	free(sp->data);
	free(sp);
	return;
}

//O(1)
int numElements(SET *sp){	//Returns the count
	assert(sp!=NULL);
	return sp->count;
}

//O(n)
char *findElement(SET *sp, char *elt){		//Calls the search fundtion to find the location of the element
	bool found;
	assert(sp!=NULL && elt!=NULL);
	int loc;
	loc = search(sp, elt, &found);
	if(found==true){
		return sp->data[loc];
	}
	else
		return NULL;
}

//O(n)
char **getElements(SET *sp){	//Creates an array for the elements in the list
	assert(sp!=NULL);
	char **elts;
	int i, j;
	elts = malloc(sizeof(char *)*sp->count);
	for(i=0,j=0;i<sp->length;i++){
		if(sp->flag[i]==1){
			elts[j] = sp->data[i];
			j++;
		}
	}
	return elts;
}








