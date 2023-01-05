#include <stdlib.h>
#include <stdio.h>
#define size 10

int counter;


union extrainfo{
	int ordernum;
	char phone[size];
};

struct order{
	int origin;
	union extrainfo extrainfo;
	char name[size];
	int drinks;
};
struct order order[size];

int add();
int fulfill();
int list();
int speclist();
