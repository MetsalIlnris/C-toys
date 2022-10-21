#include <stdio.h>
#include <time.h>

void delay(double second);

int main (void){
	delay(5.0);
	return 0;
}

void delay(double second){
	clock_t start=clock();
	//printf("start delay\n");
	clock_t now=clock();
	while(((double)(now-start))/CLOCKS_PER_SEC<second){
		now=clock();
	}
}
