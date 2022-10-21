#include<stdio.h>
#include<string.h>
#include<ctype.h>

void rank(int *group,int *bottom);
void compare(int *group,int *bottom);

int main(){
	int group[8]={1,5,8,7,6,2,5};int *i;
	printf("%d",sizeof(group)/sizeof(int));
	compare(group,group+sizeof(group)/sizeof(int));
	rank(group,group+sizeof(group)/sizeof(int));
	for(i=group;i<group+sizeof(group)/sizeof(int);i++)printf("%d",*i);
	return 0;
}

void compare(int *group,int *bottom){
	int *p,max=0,min=0; 
	for(p=group;p<bottom;p++){
		max=(max>=*p)?max:*p;
	}
	printf("最大值%d",max);
	for(p=group;p<bottom;p++){
		min=(min<=*p)?min:*p;
	}
	printf("最小值%d",min);
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
