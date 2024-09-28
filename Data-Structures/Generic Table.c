#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>	//Header file and libraries
#include <stdbool.h>
#include "set.h"

#define EMPTY 0
#define FILLED 1
#define DELETED 2	//Flag definitions

static int search(SET *sp, void *elt, bool *found);	//Hidden seach function declaration

typedef struct set{
	void **data;
	int length;
	int count;
	char *flag;
	int (*compare)();
	unsigned (*hash)();
}SET;				//SET structure declaration

//O(n)
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()){	//Create function allocates memory for the set as well as the data and the flag arrays within
	SET *sp;
	sp = malloc(sizeof(SET));
	sp->data = malloc(sizeof(void*)*maxElts);
	sp->flag = malloc(sizeof(char*)*maxElts);
	int i;
	for(i=0; i<maxElts; i++){
		sp->flag[i] = 0;}	//Flags are intitially set to empty
	assert(sp->data != NULL);
	sp->count = 0;
	sp->length = maxElts;
	sp->compare = compare;
	sp->hash = hash;
	return sp;
}

//O(n)
static int search(SET *sp, void *elt, bool *found){	//Search function checks the hash of the element and then each index after
	int idx, i, loc, available;
	available = -1;
	idx = (*sp->hash)(elt) % sp->length;
	for(i=0; i<sp->length; i++){
		loc = (idx + i) % sp->length;
		if(sp->flag[loc] == 0){
			*found = false;
			return loc;
		}
		else if(sp->flag[loc] == 2){
			if(available == -1)
				available = loc;
		}
		else if((*sp->compare)(sp->data[loc], elt)){
			*found = true;
			return loc;
		}
	}
	*found = false;
	return -1;
}

//O(n)
void addElement(SET *sp, void *elt){		//Calls the search function to find the first empty index of the hash table for the element
	bool found;
	assert(sp!=NULL && elt != NULL);
	int loc;
	loc = search(sp, elt, &found);
	if(found == false){
		sp->data[loc] = elt;	//Copies the element into the array, sets the flag to filled and increments count
		sp->flag[loc] = 1;
		sp->count ++;
	}
	return;
}

//O(n)
void removeElement(SET *sp, void *elt){		//Calls the search function to find the location of the element
	bool found;
	assert(sp!=NULL && elt != NULL);
	int loc;
	loc = search(sp, elt, &found);
	if(found == true){		//Sets flag to deleted and decrements count
		sp->flag[loc] = 2;
		sp->count --;
	}
	return;
}

//O(n)
void destroySet(SET *sp){	//Frees all the elements' pointers in the data array and then the arrays before freeing the set
	assert(sp != NULL);
	int i;
	free(sp->flag);
	free(sp->data);
	free(sp);
	return;
}

//O(1)
int numElements(SET *sp){	//returns the count
	assert(sp != NULL);
	return sp->count;
}

//O(n)
void *findElement(SET *sp, void *elt){		//Creates an array for the elements in the list
	bool found;
	assert(sp != NULL && elt!= NULL);
	int loc;
	loc = search(sp, elt, &found);
	if(found == true){
		return sp->data[loc];
	}
	else
		return NULL;
}

void *getElements(SET *sp){
	assert(sp != NULL);
	void **elts;
	int i, j;
	elts = malloc(sizeof(void*)*sp->count);
	for(i=0,j=0; i<sp->length; i++){
		if(sp->flag[i] == 1){
			elts[j] = sp->data[i];
			j++;
		}
	}
	return elts;
}













