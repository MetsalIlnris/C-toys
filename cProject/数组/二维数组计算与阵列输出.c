#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define ROWS 4
#define COLS 4

double average(int *target,int n);
void print(int m,int n,int target[m][n]);
void fileprint(int m,int n,int target[m][n]);
int calculate(int m,int n,int target[m][n]);

int main(){
	int tower[ROWS][COLS],i;
	int m=3,n=4;
	for(i=0;i<ROWS*COLS;i++)scanf("%d",tower[0]+i);
	calculate(ROWS,COLS,tower);
	printf("\n矩阵显示如下：\n");
	print(ROWS,COLS,tower);//输出在屏幕上 
	fileprint(ROWS,COLS,tower);//输出在文件上 
	
	return 0; 
	
}


double average(int *target,int n){
	int i,sum=0;
	for(i=(n-1)*COLS;i<n*COLS;i++)sum=sum+*(target+i);
	printf("第%d行的平均数为%lf",n,(double)sum/COLS);
	return (double)sum/COLS;
}

int calculate(int m,int n,int target[m][n]){
	int i,total=0;
	for(i=1;i<=m;i++){
		total+=average(target[0],i);
	}
	printf("总平均数为%lf",(double)total/(i-1));
	return 0;
}

void print(int m,int n,int target[m][n]){
	int i,k;
	for(i=0;i<m;i++){
		for(k=0;k<n;k++)printf("%5d",target[i][k]);
		putchar('\n');
	}
}

void fileprint(int m,int n,int target[m][n]){
	FILE *fp;char *name=(char*)malloc(100);
	printf("请输入一个文本名：");
	scanf("%s",name);
	if((fp=fopen(name,"a"))==NULL){
		fprintf(stderr,"Error:打开目标文件失败");
		exit(1); 
	} 
	int i,k;
	char convert[]={' ','.',',','*','!','|','^','%','#','&','@'};
	for(i=0;i<m;i++){
		for(k=0;k<n;k++){
			fprintf(fp,"%5c",convert[target[i][k]]);
		}
		fputs("\n",fp);
	}
	fclose(fp); 
}

