/*
 *
 *	Coen 12 - Project 5, Priority List
 *	Jack Landers
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "pqueue.h"	//includes header files

struct pqueue{		//declares queue structure
	int count;
	int length;
	void **data;
	int (*compare)();
};

PQ *createQueue(int (*compare)()){	//O(1)
	struct pqueue *pq;
	pq = malloc(sizeof(PQ));	//allocate space for queue
	pq->count = 0;
	pq->length = 10;
	pq->compare = compare;
	pq->data = malloc(sizeof(void *)*pq->length); //allocate space for data
	assert(pq->data!=NULL);
	return pq;
}

void addEntry(PQ *pq, void *entry){	//O(n)
	assert(pq != NULL);
	if(pq->count == pq->length){
		pq->length = pq->length*2;
		pq->data = realloc(pq->data, sizeof(void *)*pq->length);	//reallocate space if too small
	}
	if(pq->data[0] == NULL){
		pq->data[0] = entry;
		return;
	}
	int last, i;
	void *temp;
	i = (pq->count-1)/2;
	last = pq->count;
	pq->data[last] = entry;
	
	while((last > 0) && (*pq->compare)(pq->data[i], pq->data[last]) < 0){	//swaps with parent if entry is greater
		temp = pq->data[i]; 			
		pq->data[i] = pq->data[last];
		pq->data[last] = temp;
		last = i;
		i = (i-1)/2;
	}
	pq->count++;
	return;
}

void *removeEntry(PQ *pq){	//O(n)
	assert(pq != NULL);
	
	int left, right, i, min;	
	void *temp, *result;

	i = 0;
	left = 1;
	right = 2;

	pq->count--;
	result = pq->data[0];	//returns root
	pq->data[0] = pq->data[pq->count];	//sets root to final leaf

	while(left < pq->count){	//checks if there is a left child
		min = left;
		if(right < pq->count){	//checks if there is a right child
			if((*pq->compare)(pq->data[left], pq->data[right]) > 0){	//compares left and right child
				min = right;
			}
		}
		if((*pq->compare)(pq->data[i], pq->data[min]) < 0){	//swaps smallest child with min
			temp = pq->data[i];
			pq->data[i] = pq->data[min];
			pq->data[min] = temp;
			i = min;
		}
		else{
			break;
		}
		left = 2*i +1;
		right = 2*i +2;
	}
	return result;		
}

void destroyQueue(PQ *pq){	//O(1)
	assert(pq != NULL);
	int i;
	free(pq->data);
	free(pq);
}

int numEntries(PQ *pq){	//O(1)
	assert(pq != NULL);
	return pq->count;
}



