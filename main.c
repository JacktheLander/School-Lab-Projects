#include "stm32l476xx.h"
#include "SysClock.h"

int fiblist[25];
char string1[] = "Hello\0";
char string2[] = "World\0";
char string3[255];

int main(void){

	System_Clock_Init(); // Switch System Clock = 80 MHz
	
	int i;
	fiblist[0]=0;
	fiblist[1]=1;
	for(i=2;i<25;i++){
		fiblist[i]=fiblist[i-1]+fiblist[i-2];
	}
	char *ptr1 = string1;
	char *ptr2 = string3;
	while(*ptr1 != '\0'){
		*ptr2 = *ptr1;
		ptr2 ++;
		ptr1 ++;
	}
	*ptr2 = ' ';
  ptr2++;
	ptr1 = string2;
	while(*ptr1 != '\0'){
		*ptr2 = *ptr1;
		ptr2 ++;
		ptr1 ++;
	}
	while(1) {

}
}
