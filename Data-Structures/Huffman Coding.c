#include <stdio.h>
#include <stdlib.h>
#include <assert.h>	
#include <string.h>
#include <stdbool.h>
#include "pack.h"	//header files
#include "pqueue.h"
#include <ctype.h>

struct node *nodes[257];

static int compare(struct node *temp1, struct node *temp2);

static struct node *mknode(int data, struct node *left, struct node *right);

static int depth(struct node *np);	//functions declarations

int main(int argc, char *argv[]){	//O(n)
	
	if(argc != 3){		//verifies the right number of variables
		return 0;
	}
	
	int i, c, j;
	int counts[257];	//declares int variables

	for (i=0; i<257; i++){		//sets arrays to 0 and null
		counts[i] = 0;
		nodes[i] = NULL;
	}
	
	FILE *fp = fopen(argv[1], "r"); 	//opens file to read 
		
	while((c = getc(fp)) != EOF){		//counts each character in counts array
		counts[c] ++;
	}

	struct node *r1, *r2;	//declares child nodes
	
	struct pqueue *pq = createQueue(compare);	//creates queue pq

	for(j=0; j<256; j++){
		if(counts[j]>0){	//adds all characters counted to nodes array
			nodes[j] = mknode(counts[j], NULL, NULL);
			addEntry(pq, nodes[j]);
			}
	}
	nodes[256] = mknode(0, NULL, NULL);
	addEntry(pq, nodes[256]);
	
	while(numEntries(pq) > 1){
		r1 = removeEntry(pq);
		r2 = removeEntry(pq);
		addEntry(pq, mknode(r1->count + r2->count, r1, r2));	//sums children nodes and replaces with a parent
	}

	for(c=0; c<257; c++){		//prints
		if(nodes[c]){
			if(!isprint(c)){
				printf("%03o", c);
			}
			else{
				printf("'%c' : %d X %d = %d\n", c, counts[c], depth(nodes[c]), counts[c]*depth(nodes[i]));
			}
		}
	} 
	pack(argv[1], argv[2], nodes);
	return 0;
}
	
static struct node *mknode(int data, struct node *left, struct node *right){	//O(1)
	struct node *np;
	np = malloc(sizeof(struct node));
	assert(np != NULL);
	np->count = data;
	np->parent = NULL;	//creates parent node for left and right nodes
	if(left != NULL){
		left->parent = np;
	}
	if(right != NULL){
		right->parent = np;
	}
	return np;

}

static int compare(struct node *temp1, struct node *temp2){	//O(1)
	return (temp1->count < temp2->count) ? -1 : (temp1->count > temp2->count);
}	 
	
static int depth(struct node *np){	//O(1)
	return np->parent == NULL ? 0 : 1 + depth(np->parent);
}





