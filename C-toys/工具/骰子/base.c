#include<stdio.h>
#include<time.h>

static unsigned long int seed=1;

unsigned int product(void){
	seed=seed*1103515245+12345;
	return (unsigned int) (seed/65536)%32758;
	seed++;
}


void rank(int *group,int *bottom){
	int *i=0,*k=0,cac=0,*count=0;
	for(i=group;i<bottom;i++){
		for(k=count=i;k<bottom;k++)if(*k>*count)count=k;
		cac=*i;
		*i=*count;
		*(group+(count-group))=cac;
	}
	
}
