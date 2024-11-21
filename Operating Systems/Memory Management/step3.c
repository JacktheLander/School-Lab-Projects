#include <stdio.h>
#include <stdlib.h>

int main(){
	char inputBuffer[100];
	int page_num;

	while(fgets(inputBuffer, 100, stdin)){
		page_num = atoi(inputBuffer);
		printf("Miss: Page %d \n", page_num);
	}

}
