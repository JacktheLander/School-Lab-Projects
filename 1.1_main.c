#include <stdio.h>
#include <stdlib.h>

/* Mean, median, and mode calculator */

float mean(float *);
float median(float *);
float mode(float *);

int main(int argc, char *argv[]) {
	
	float array[20];
	int i;
	for(i=0;i<10;i++){
		array[i]=i+1;
		printf("%f\n", array[i]);
	}
	for(i=10;i<20;i++){
		array[i]= 29-i;
		printf("%f\n", array[i]);
	}
	
	float x = mean(array);
	float y = median(array);
	float z = mode(array);
	
	printf("The mean is: %f\n", x);
	printf("The median is: %f\n", y);
	printf("The mode is: %f\n", z);
	
	return 0;
}

float mean(float *a){		//sum should equal 200 and avg should return 10
	float sum;
	int j;
	int size = 20;
	for(j=0;j<20;j++){
		sum += a[j];
	}
	return sum/size;
}

float median(float *b){		//median should return 19
	int middle = 10;
	return b[middle];
}

float mode(float *c){		//mode should return 10
	int k;
	int l;
	int count;
	int maxcount = 0;
	int max;
	for(k=0;k<20;k++){
		count = 0;
		for(l=0;l<20;l++){
			if(c[k]==c[l]){
				count++;
			}
		}
		if(count>maxcount){
			maxcount = count;
			max = k;
		}
	}
	return c[max];
}
