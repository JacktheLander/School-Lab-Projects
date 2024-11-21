#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct{
	int pageno;
	int last_accessed;
}ref_page;

int main(int argc, char* argv[]){
	

	int cacheSize = atoi(argv[1]);
	ref_page cache[cacheSize];

	char inputBuffer[100];
	int totalFaults = 0;
	int counter = 0;
	
	for (int i = 0; i < cacheSize; ++i) {
		cache[i].pageno = -1;
		cache[i].last_accessed = 0;
	}
	
	while(fgets(inputBuffer, 100, stdin)){
		int page_num = atoi(inputBuffer);
		bool foundInCache = false;
		counter++;

		for(int i=0; i<cacheSize; i++){
			if(cache[i].pageno == page_num){
				foundInCache = true;
				cache[i].last_accessed = counter;
				break;
			}
		}
		if(foundInCache == false){
			printf("Miss: Page %d \n", page_num);
			totalFaults++;
			
			int min_idx = 0;
			for(int j=1; j<cacheSize; j++){
				if(cache[j].pageno == -1 || cache[j].last_accessed < cache[min_idx].last_accessed){
					min_idx = j;
				}
			}
			cache[min_idx].pageno = page_num;
			cache[min_idx].last_accessed = counter;
		}
	}

}
