#include<stdio.h>
#include<ctype.h>


int get_alpha(void);
char get_firstchar(void);

int main(void){

	return 0;
}

char get_firstchar(void){
	char ch,ret;short int haschange=0;
	printf("***输入文段检索首个非空字符***\n");
	while((ch=getchar())!=EOF){
		if(!ispunct(ch)&&!isspace(ch)&&haschange==0){
		ret=ch;
		haschange=1;
		}
	}
	printf("首个非空字符为%c\n",ret);
	return ret;
}


int get_alpha(void){
	int ch;
	printf("***输入文段检索所有的字母***/n");
	while((ch=getchar())!=EOF){
		if(isalpha(ch)){
			printf("检索到字母%c\n",ch);
			if(isupper(ch))ch=ch-'A'+'a';
			printf("该字母在字母表中处于第%d位\n",ch-'a'+1);
		}
	}
	return 0;
}
