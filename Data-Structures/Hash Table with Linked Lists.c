#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "list.h"
#include "set.h"

#define avg 20;

typedef struct set{
	LIST **list;
	int length;
	int count;
	int (*compare)();
	unsigned (*hash)();
}SET;

SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()){
	SET *sp;
	sp = malloc(sizeof(SET));
	sp->length = maxElts/avg;
	sp->count = 0;
	sp->compare = compare;
	sp->hash = hash;
	int i;
	sp->list = malloc(sizeof(LIST *) * sp->length);
	for(i=0; i<sp->length; i++){
		sp->list[i] = createList(compare);}
	return sp;
}

void destroySet(SET *sp){
	assert(sp != NULL);
	int i;
	for(i=0; i<sp->length; i++){	
		destroyList(sp->list[i]);}
	free(sp->list);
	free(sp);
	return;
}

int numElements(SET *sp){
	assert(sp != NULL);
	return sp->count;
}

void addElement(SET *sp, void *elt){
	assert(sp != NULL && elt != NULL);
	int loc;
	loc = (*sp->hash)(elt) % sp->length;
	if(findItem(sp->list[loc], elt) == NULL){
		addFirst(sp->list[loc], elt);
		sp->count ++;
	}
	return;
}

void removeElement(SET *sp, void *elt){
	assert(sp != NULL && elt != NULL);
	int loc;
	loc = (*sp->hash)(elt) % sp->length;
	if(findItem(sp->list[loc], elt) != NULL){
		removeItem(sp->list[loc], elt);
		sp->count --;
	}
	return;
}

void *findElement(SET *sp, void *elt){
	assert(sp != NULL && elt != NULL);
	int loc;
	loc = (*sp->hash)(elt) % sp->length;
	return findItem(sp->list[loc], elt);
}

void *getElements(SET *sp){
	assert(sp != NULL);
	void **elts;
	void **items;
	int i, j;
	elts = malloc(sizeof(void *) * sp->count);
	assert(elts != NULL);
	for(i=0,j=0; i<sp->length; i++){
		items = getItems(sp->list[i]);
		memcpy(elts + j, items, sizeof(void *) * numItems(sp->list[i]));
		j += numItems(sp->list[i]);
		free(items);	
	}
	return elts;
}


	










