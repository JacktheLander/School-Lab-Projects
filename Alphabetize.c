#include <stdio.h>
#include <stdlib.h>

char str1[] = "Hello";
char str2[] = "Dog";
char str3[] = "Cat";
char str4[] = "rabbit";
char str5[] = "man";
char str6[] = "woman";
char str7[] = "person";
char str8[] = "camera";
char str9[] = "TV";
char str10[] = "clueless";
char *slist[10] = {str1, str2, str3, str4, str5, str6, str7, str8, str9, str10};

//Alphabetizes by iterating through the strings and replacing i with the next smallest string
int main(int argc, char *argv[]) {
	int i, j, p;
	char *temp, *cmpj, *cmpi;
	for(i=0;i<10;i++){
		for(j=i+1;j<10;j++){
			cmpi = slist[i];
			cmpj = slist[j];
			if(*cmpi < 96){
				*cmpi += 32;
			}
			if(*cmpj < 96){
				*cmpj += 32;
			}
			while(*cmpj==*cmpi){
				cmpi++;
				cmpj++;
			}
			if(*cmpj<*cmpi){
				temp=slist[i];
				slist[i]=slist[j];
				slist[j]=temp;
			}
		}
	}
	for(p=0;p<10;p++){
		printf("%s\n", slist[p]);
	}
}
