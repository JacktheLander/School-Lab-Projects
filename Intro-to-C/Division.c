#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int division(int, int, int, int);

int main (void){
	int score = 0;
	int i;
	int divisor, dividend, quotient;	//Declares variables and random function
	
	for(i=0; i<10; i++){
		srand(time(NULL));

		divisor = rand()%12+1;	//Randomly generates 2 numbers 1 to 12
		quotient = rand()%12+1;
		dividend = divisor*quotient;
	
		if(division(dividend, quotient, divisor, i) == 1){		//calls division function
			score++;
		}
	}
	printf("You scored %d out of 10", score);
}	


int division (int dividend, int quotient, int divisor, int i){		//declares division function

	int answer;
	printf("What is %d divided by %d?\n", dividend, divisor);
	scanf("%d", &answer);
	
	if(answer == quotient){		//Checks answers
		printf("1\n");
		return 1;}
	else{
		printf("0\nThe correct answer is %d\n", quotient);
		return 0;}
}
