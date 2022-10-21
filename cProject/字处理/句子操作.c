#include<stdio.h>
#include<string.h>
#include<ctype.h>

void del(char *str);
void backward(char *str);

int main(void){
	char sentence[]="hello world&*&?jskdjf";
	puts(sentence);
	del(sentence);
	puts(sentence);
	return 0;
} 

void del(char *str){
	int size=strlen(str),i=0,cnt=0;
	for(i=0,cnt=0;i<size;i++)
		if(isalpha(*(str+i))){
			*(str+cnt)=*(str+i);
			cnt++;
		}
	*(str+cnt)='\0';
}//此程序将删除目标字符串中的非字母部分 


void backward(char *str){
	int i;
	int size=strlen(str);
	int store[size];
	for(i=1;i<=size;i++)*(store+i)=*(str+size-i);
	for(i=1;i<=size;i++)*(str+i-1)=store[i];
}//此程序将倒序改写目标字符串 

	
