#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void main(int argc, char *argv[]){
	char buffer[10000];
	FILE *fp, *fp_write;
	char new_file[256];
	
	strcpy(new_file, argv[1]);
        strcat(new_file, "_copy");

	fp = fopen(argv[1], "rb");
	fp_write = fopen(new_file, "wb");

	size_t bytes_read;

	while ((bytes_read = fread(buffer, sizeof(buffer), 1, fp)) > 0){
		fwrite(buffer, 1, bytes_read, fp_write);
	}
	fclose(fp);
	fclose(fp_write);
	return;
}
