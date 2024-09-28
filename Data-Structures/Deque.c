/*
 *
 *	COEN 12 - Project 4, Part 1 - Deque
 *	Jack Landers
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "list.h"

struct list{
	int count;
	struct node *head;
	int (*compare)();
};
typedef struct list List;

struct node{
	void *data;
	struct node *next;
	struct node *prev;
};
typedef struct node NODE;

LIST *createList(int(*compare)()){
	struct list *lp;
	lp = malloc(sizeof(struct list));
	assert(lp != NULL);
	lp->count = 0;
	lp->compare = compare;
	lp->head = malloc(sizeof(struct node));
	assert(lp->head != NULL);
	lp->head->next = lp->head;
	lp->head->prev = lp->head;
	return lp;
}

void destroyList(LIST *lp){
	assert(lp != NULL);
	NODE *pdel = lp->head->prev;
	NODE *pprev;
	while(pdel != lp->head){
		pprev = pdel->prev;
		free(pdel);
		pdel = pprev;
	}
	free(pdel);
	free(lp);
	return;
}

int numItems(LIST *lp){
	assert(lp != NULL);
	return lp->count;
}

void addFirst(LIST *lp, void *item){
	assert(lp != NULL && item != NULL);
	NODE *pnew = malloc(sizeof(struct node));
	pnew->data = item;
	pnew->next = lp->head->next;
	pnew->prev = lp->head;
	lp->head->next->prev = pnew;
	lp->head->next = pnew;
	lp->count ++;
	return;
}
	
void addLast(LIST *lp, void *item){
	assert(lp != NULL && item != NULL);
	NODE *pnew = malloc(sizeof(struct node));
	pnew->data = item;
	pnew->prev = lp->head->prev;
	pnew->next = lp->head;
	lp->head->prev->next = pnew;
	lp->head->prev = pnew;
	lp->count ++;
	return;
}

void *removeFirst(LIST *lp){
	assert(lp != NULL && lp->head->next != lp->head);
	NODE *pdel = malloc(sizeof(struct node));
	pdel = lp->head->next;
	pdel->next->prev = lp->head;
	lp->head->next = pdel->next;
	lp->count --;
	//free(pdel);
	return pdel->data;
}

void *removeLast(LIST *lp){
	assert(lp != NULL && lp->head->prev != lp->head);
	NODE *pdel = malloc(sizeof(struct node));
	pdel = lp->head->prev;
	pdel->prev->next = lp->head;
	lp->head->prev = pdel->prev;
	lp->count --;
	//free(pdel);
	return pdel->data;
}

void *getFirst(LIST *lp){
	assert(lp != NULL && lp->head->next != lp->head);
	return lp->head->next->data;
}

void *getLast(LIST *lp){
	assert(lp != NULL && lp->head->prev != lp->head);
	return lp->head->prev->data;
}

void *findItem(LIST *lp, void *item){
	assert(lp != NULL && item != NULL);
	NODE *p = malloc(sizeof(struct node));
	p = lp->head->next;
	while(p != lp->head){
		if((lp->compare)(p->data, item) == 1)
			return p->data;
		p = p->next;
	}
	free(p);
	return;
}

void removeItem(LIST *lp, void *item){
	assert(lp != NULL && item != NULL);
	NODE *p = malloc(sizeof(struct node));
	p = lp->head->next;
	while(p != lp->head){
		if((lp->compare)(p->data, item) == 1){
			p->prev->next = p->next;
			p->next->prev = p->prev;
			lp->count --;
			return;
		}
		p = p->next;
	}
	return;
}

void *getItems(LIST *lp){
	assert(lp != NULL);
	return lp;
}
	












