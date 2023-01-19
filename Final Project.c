/*
 *
 *	Coen 12 - Term Project, doubly linked list of queues
 *	Jack Landers
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "list.h"	//Header files included
#define QLENGTH 10	//Queue length defined constant

struct list{
	int count;
	struct node *head;
};
typedef struct list LIST;	//list structure declaration

struct node{
	void **queue[QLENGTH];
	int first;
	int count;
	struct node *next;
	struct node *prev;
};
typedef struct node NODE;	//node structure declaration

LIST *createList(void){		//doubly linked list of nodes is created with queues
	struct list *lp;
	lp = malloc(sizeof(struct list));
	assert(lp!=NULL);
	lp->count = 0;
	lp->head = malloc(sizeof(struct node));
	assert(lp->head != NULL);
	lp->head->next = lp->head;
	lp->head->prev = lp->head;
	lp->head->first = NULL;
	lp->head->count = NULL;
	return lp;
}

void destroyList(LIST *lp){	//O(n)
	assert(lp != NULL);
	NODE *pdel = malloc(sizeof(struct node));
	pdel = lp->head->prev->prev;
	while(pdel != lp->head){	//pdel node traverses back through the list deleting all the nodes
		free(pdel->next);
		pdel = pdel->prev;
	}
	free(lp->head);
	free(lp);
	return;
}

int numItems(LIST *lp){		//O(n)
	assert(lp != NULL);
	NODE *p = malloc(sizeof(struct node));
	int count = 0;
	while(p != lp->head){
		count += p->count;	//p traverses all the nodes summing their counts
		p = p->next;
	}	
	return count;
}

void addFirst(LIST *lp, void *item){	//O(1)
	assert(lp != NULL && item != NULL);
	if(lp->head->next->count == QLENGTH){	//a new node is created at the start of the list and item is the first in its queue
		NODE *pnew = malloc(sizeof(struct node));
		pnew->queue[0] = item;
		pnew->next = lp->head->next;
		pnew->prev = lp->head;
		pnew->next->prev = pnew;
		lp->head->next = pnew;
		pnew->first = 0;
		lp->count ++;
	}
	else{		//or the item is added to the queue in the first node
		lp->head->next->queue[(lp->head->next->first + lp->head->next->count - 1) % QLENGTH] = item;
	}
	lp->head->next->count ++;	//count incremented
	return;
}

void addLast(LIST *lp, void *item){	//O(1)
	assert(lp != NULL && item != NULL);
	NODE *pnew = malloc(sizeof(struct node));
	if(lp->head->prev->count == QLENGTH){	//a new node is created at the end of the list and the item is added to the queue
		NODE *pnew = malloc(sizeof(struct node));
		pnew->queue[0] = item;
		pnew->prev = lp->head->prev;
		pnew->next = lp->head;
		pnew->prev->next = pnew;
		lp->head->prev = pnew;
		pnew->first = 0;
		lp->count ++;
	}
	else{		//or the item is added to the last queue in the list
		int i;
		i = (lp->head->prev->first + lp->head->prev->count - 1) % QLENGTH;
		lp->head->prev->queue[i] = item;
	}
	lp->head->prev->count ++;	//count incremented
	return;
}

void *removeFirst(LIST *lp){	//O(1)
	assert(lp != NULL);
	if(lp->head->next->count == 1){	//the first node is deleted
		NODE *pdel = malloc(sizeof(struct node));
		pdel = lp->head->next;
		lp->head->next = pdel->next;
		pdel->next->prev = lp->head;
		lp->count --;
		return pdel->queue[pdel->first];
	}
	else{	//or the last item in the first queue is deleted
		lp->head->next->count --;
		return lp->head->next->queue[(lp->head->next->first + lp->head->next->count - 1) % QLENGTH];
	}
}

void *removeLast(LIST *lp){	//O(1)
	assert(lp != NULL);
	if(lp->head->prev->count == 1){	//the last node is deleted
		NODE *pdel = malloc(sizeof(struct node));
		pdel = lp->head->prev;
		pdel->prev->next = lp->head;
		lp->head->prev = pdel;
		lp->count --;
		return pdel->queue[pdel->first];
	}
	else{	//or the last item in the last queue is deleted
		int del;
		del = (lp->head->prev->first + lp->head->prev->count - 1) % QLENGTH;
		lp->head->prev->count--;
		return lp->head->prev->queue[del];
	}
}

void *getFirst(LIST *lp){	//O(1)
	assert(lp != NULL);
	return lp->head->next->queue[lp->head->next->first];
}

void *getLast(LIST *lp){	//O(1)
	assert(lp != NULL);
	return lp->head->prev->queue[(lp->head->prev->first + lp->head->prev->count - 1) % QLENGTH];
} //calculated the last item by adding the count to the index of first, subtracting 1, and modding the length for overflow

void *getItem(LIST *lp, int index){	//O(n)
	assert(lp != NULL);
	NODE *p = malloc(sizeof(struct node));
	p = lp->head->next;
	while(index > p->count){	//finds the node with the index
		index -= p->count;
		p = p->next;
	}
	return p->queue[(p->first + index) % QLENGTH];	//returns the item from the queue
}

void setItem(LIST *lp, int index, void *item){		//O(n)
	assert(lp != NULL);
	NODE *p = malloc(sizeof(struct node));
	p = lp->head->next;
	while(index > p->count){	//finds the node with the index
		index -= p->count;
		p = p->next;
	}
	p->queue[(p->first + index) % QLENGTH] = item;	//sets the item in the queue
	return;
}








