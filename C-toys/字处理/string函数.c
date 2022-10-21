#include<stdio.h>
#include<string.h>

char *strchr0(char *str,char ch);
int lenth(char *str);
char *strncpy0(char *str1,char *str2,int n); 
char *strncpy1(char *str1,char *str2,int n); 
	
int main(void){
	char string[20],ch,*result;
	//string=(char*)malloc(1024);
	while(1){
		printf("请输入一段文字：\n");	
		fgets(string,20,stdin);
		printf("\n请输入一个字符：\n");
		scanf("%c",&ch);
		result=strchr0(string,ch); //strchr函数寻找目标字符· 
		if(result==NULL)printf("未找到该字符。");
		else printf("在地址%p找到字符%c",result,ch);
		do{
		ch=getchar();
		}while(ch!=EOF&&ch!='\n');//清空缓存区 
	}
} 

int lenth(char *str){
	char *p=str;int cnt=0;
	while(*p++!='\0')cnt++;
	return cnt;//返回输入的字符串长度 
}

char *strchr0(char *str,char ch){
	char *p;
	for(p=str;*p!='\0';p++){
		if(*p==ch)break;
	};
	if(*p=='\0')return NULL;
	else return p;
}

char *strncpy0(char *str1,char *str2,int n){
	char *p=str1,*q=str2;
	while(*q!='\0'&&(q-str2)<n){
		*p=*q;
		p++;
		q++;
	}
	if(lenth(str2)<n){
		*(q+1)='\0';
	}
	return str1;
} 


char *strstr0(char *str1,char *str2){
	char *p=str1;int cnt=0;
//	printf("%d,%d,%p,%p",lenth(str1),lenth(str2),p,str1+sizeof(char)*(lenth(str1)-lenth(str2)));
	if(lenth(str1)<lenth(str2));
	else{
		while(p<=(str1+sizeof(char)*(lenth(str1)-lenth(str2)))){
//			printf("开始判断\n");
			for(cnt=0;cnt<=lenth(str2);cnt++){
//				printf("当前位置%d，cnt=%d\n",p-str1,cnt);
				if(*(p+cnt)!=*(str2+cnt)){
//					printf("寻找第%d位置结束\n",p-str1+1);
					break;//发现不相等字符立刻终止该次比较 
				}
			}
			if(cnt==lenth(str2)){
//				printf("成功找到目标\n");
				return p; 
			}
			else p++;//str2全部比较相等则返回p，否则进行下一轮比较 
		}
	}
//	printf("未找到目标");
	return NULL;
}


char *strstr1(char *str1,char *str2){
	int cnt=0;char *end=str1+sizeof(char)*(lenth(str1)-lenth(str2));
	printf("%d,%d,%p",lenth(str1),lenth(str2),str1+sizeof(char)*(lenth(str1)-lenth(str2)));
	if(lenth(str1)<lenth(str2));
	else{
		while(str1<end&&cnt<lenth(str2)){
			printf("开始判断\n");
			for(cnt=0;cnt<lenth(str2);cnt++){
				printf("当前位置%d，cnt=%d\n",str1,cnt);
				if(*(str1+cnt)!=*(str2+cnt)){
				printf("寻找第%d位置结束\n",str1);
					break;//发现不相等字符立刻终止该次比较 
				}
			}
			str1++;
		}
	}
	if(cnt=lenth(str2)){
		printf("找到目标");
		return str1;
	}
	printf("未找到目标");
	return NULL;
}


	
