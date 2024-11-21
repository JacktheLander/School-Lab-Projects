#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char* argv[]){
	typedef struct{
		int pageno;
		int binary;
	}ref_page;

	int cacheSize = atoi(argv[1]);
	ref_page cache[cacheSize];

	char inputBuffer[100];
	int totalFaults = 0;
	int page_num;
	int placeInArray = 0;

	for (int i = 0; i < cacheSize; ++i) {
		cache[i].pageno = -1;
		cache[i].binary = 0;
	}
	
	while(fgets(inputBuffer, 100, stdin)){
		page_num = atoi(inputBuffer);
		bool foundInCache = false;

		for(int i=0; i<cacheSize; i++){
			if(cache[i].pageno == page_num){
				foundInCache = true;
				cache[i].binary = 1;
				break;
			}
		}
		if(foundInCache == false){
			printf("Miss: Page %d \n", page_num);
			totalFaults++;

			while(cache[placeInArray].binary == 1){
				cache[placeInArray].binary = 0;
				placeInArray = (placeInArray + 1)% cacheSize;
			}
			cache[placeInArray].pageno = page_num;
			placeInArray = (placeInArray + 1)% cacheSize;
		}

	}

}
