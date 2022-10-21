
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void checkout(int *p) {
	int c;
	while(scanf("%d", p)!=1){
		printf("输入有误，请重新输入:");
		while ((c = getchar()) != EOF && c != '\n');
	}
}

int add() {
	//int a,i;
	//for(i=0;i<10;i++){
	//a=rand()%3;
	//printf("%d  ",a);
	//}
    printf("使用加法功能请按1，使用减法功能请按2\n");
    int n=0;
    scanf("%d", &n);
    if (n==2){
    int a;
    int b;
    printf("请输入被减数：");
    scanf("%d", &a);
    printf("请输入减数：");
    scanf("%d", &b);
    int change = a-b;
    printf("得到%d。\n", change);
    }
    if(n==1){
    int a;
    int b;
    printf("请输入被加数：");
	checkout(&a);
    printf("请输入加数：");
    checkout(&b);
    int change = a+b;

    printf("得到%d。\n", change);
    }
    getchar();
    return 0;
}

int analyze(){
	printf("***载入素数判断工具***\n"); 
	printf("输入-1代表结束\n");
int a,x=0,RESULT;
while(1){
    a=2;RESULT=1;
    printf("请输入\n");
    checkout(&x);
    if(x==-1)break;
	if(x==1)printf("error:该数为1\n");
    else if(x<9999) {
        while((a<x)&&(RESULT!=0)){
	    	RESULT=x%a;
	    	a++;
        } 
		if(a==x)printf("数%d为素数\n",x);
    	else(printf("数%d为合数\n",x)) ;
    }
    else{
		printf("error:数值过大无法分析\n");
    };
   
    }
 	printf("结束\n") ;
    return 0;
}

int main()

{
	printf("***欢迎使用计算器***\n");
	printf("计算器功能请按1；素数判断请按2；\n");
	analyze();
	
	return 0;
}

