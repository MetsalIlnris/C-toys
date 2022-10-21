#include<stdio.h>
#include<ctype.h>
#define STOP '|'
#define SIZE 8


void get_firstword(int len);
int sum(void);
int fun(char *s);

int main(){
	printf("%d",fun("hello,  asd world   "));
	//get_firstword(SIZE);
	return 0;
} 

int sum(void){
	char prev='\n',c;int word=0,count=0;
	printf("***本程序用来测量英文段单词数与字符数***\n");
	while((c=getchar())!=EOF){
		if((!ispunct(c)&&!isspace(c))&&(isspace(prev)||ispunct(prev)))word++;
		if(!ispunct(c)&&!isspace(c))count++;
		prev=c;
	}
	printf("单词数量为%d,字符数量为%d,平均每个单词有%lf个字符",word,count,(double)count/(double)word);
	
	return 0;

}


void get_firstword(int len){
	printf("***输入文段读取首个单词***\n");
	char word[len],ch=0;int i=1;
	while(!isalpha(ch=getchar())); 
	word[0]=ch;
	while((isalpha(ch=getchar()))&&(i<len)){
		word[i]=ch;
		i++;
	}
	word[i]='\0' ;
	puts(word); 
} 

//int fun(char *s){
//	char c=*s,prev='\n';int word=0,i=0;
//	while(c!='\0'){
//		if(c>='a'&&c<='z'&&(prev<'a'||prev>'z'))word++;
//		prev=c;
//		i++;
//		c=*(s+i);
//	}
//	
//	return word;
//
//}

int fun(char *s)
{
  int i,j=0;
  for(i=0;s[i]!='\0';i++)
     if(s[i]!=' '&&(s[i+1]==' '||s[i+1]=='\0'))   /*如果一个字母的下一个字符为空格或者结束标记，则表示一个单词结束*/
        j++;
  return j;           /*返回单词个数*/
}

 
