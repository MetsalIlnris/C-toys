#include<stdio.h>
#include<string.h>
#include<ctype.h>

void copy1(int *group,int *bottom,int*);

int main(){
	int group[3][3]={2,1,4,5,6,7,8,9},copy[3][3];int *i;
	printf("%d",sizeof(group)/sizeof(int));
	copy1(group[0],group[0]+sizeof(group)/sizeof(int),copy[0]);//复制 
	for(i=copy[0];i<copy[0]+sizeof(copy)/sizeof(int);i++)printf("%d\n",*i);//数组输出显示 
	return 0;
}

void copy1(int *group,int *bottom,int *target){
	int count=0;
	for(;count<bottom-group;target++,count++)*target=*(group+count);
}
