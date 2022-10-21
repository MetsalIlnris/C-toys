#include<stdio.h>
#include<time.h>

static unsigned long int seed=(unsigned int)20201001509;

unsigned int product(void){
	seed=seed*1103515245+12345;
	return (unsigned int) (seed/65536)%32758;
	seed++;
}

int main (){
//	unsigned int text_number=product()%(unsigned int)32;
//	printf("%dÌâ",text_number);
	int i=1,text[3];
	
	text[0]=srand(20201001509)%32+1;
	text[1]=rand()%32+1;
	text[2]=rand()%32+1;
	for(i=0;i<3;i++){
		printf("%d\n",text[i]);
	}

	return 0;
} 
