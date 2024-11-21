#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	typedef struct {
		int pageno; //Any other useful values associated with the page, e.g. referenced
	} ref_page;
	
	char inputBuffer[100]; // Buffer to hold input from test file
	int totalFaults = 0; // keeps track of the total page fault
	int cacheSize = atoi(argv[1]); // Size of Cache passed by user
	
	ref_page cache[cacheSize]; // Virtual cache for simulator
	FILE *fp;
	
	int i;
	fp = fopen("testInput.txt", "w");
	for (i=0; i<9; i++){ //Use a number you can test by hand, >possiblePages to force cache hits
		int page = rand() % 12;
		sprintf(inputBuffer, "%d\n", page); //Small for hand testing, >cacheSize to force cache miss
		fputs(inputBuffer, fp);
	}
	fclose(fp);
	return 0;
}
