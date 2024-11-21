#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int cacheSize = atoi(argv[1]); // Size of Cache passed by user
	FILE *fp;
	char buffer [sizeof(int)];
	int i;
	fp = fopen("testInput.txt", "w");
	for (i=0; i<9; i++){ //Use a number you can test by hand, >possiblePages to force cache hits
		sprintf(buffer, "%d\n", rand()%24); //Small for hand testing, >cacheSize to force cache miss
		fputs(buffer, fp);
	}
	fclose(fp);
	return 0;
}
