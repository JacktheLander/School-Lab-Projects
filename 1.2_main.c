#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int i;
	unsigned long array[] = {652546067, 71031077, 73292866, 420696291, 216085900,  1591050919, 1577964071, 2298416818};
	for(i=0;i<8;i++){
		unsigned long seconds = array[i];
		unsigned long minutes = (seconds/60) % 60;
		unsigned long hours = (seconds/(60*60)) % 24;
		unsigned long day = (seconds/(24*60*60)) % 30;
		unsigned long month = (seconds/(30*24*60*60)) % 12;
		unsigned long years = 1950 + (seconds/(365*24*60*60));
		
		
		
		
		if(minutes<10){
			printf("%d/%d, %d, %d:0%d\n", month, day, years, hours, minutes);
		}
		else{
			printf("%d/%d, %d, %d:%d\n", month, day, years, hours, minutes);
		}	
	}	
	while(1){		
	}
	return 0;
}
