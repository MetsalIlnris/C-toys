#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define BSIZE 20
#define NSIZE 6


struct book{
	char name[NSIZE];
	_Bool isblank;
	char infor[100];
};


char buffer[50];

char show_menu(void);
int add(struct book books[]);
int del(struct book books[]);
void read(struct book target[]);
void print(struct book target[]);
void save(struct book target[]);

struct book books[BSIZE];

int main(){
	puts("程序加载中");
	int i=0;char ch;
	for(i=0;i<BSIZE;i++){
		books[i].isblank=1;
	}
	while(ch!='q'&&ch!=EOF){
		switch (ch=show_menu()){
			case 'a':add(books);
			break;
			case 'd':del(books);
			break;
			case 'r':read(books);
			break;
			case 's':save(books);
			break;
			case 'p':print(books);
			break;
			default:break;
		}
	}
	puts("程序结束");
	return 0; 
}


char show_menu(void){
	puts("\n____________________________________________________\n\n");
	puts("*****欢迎使用图书管理程序*****\n");
	puts("a)add增加图书    d)del删除图书         r)read读入数据\n"); 
	puts("s)save保存数据   p)print显示所有图书   q)quit退出\n"); 
	puts("______________________________________________________\n\n");
	char ch='0',c='0'; 
	ch=tolower(getchar());
	while ((c = getchar()) != EOF && c != '\n');//清空缓存区 
	//printf("%c %c",ch,c);
	return ch;
}


int add(struct book books[]){
	int i=0;char c;
	for(i=0;i<BSIZE;i++){
		if(books[i].isblank==1)break;
	}
	if(i==BSIZE){
		fputs("Error:Don't have enough space\n",stderr);
		return 1;
	}
	puts("请输入书名\n");
	scanf("%s",buffer);
	if(strlen(buffer)>NSIZE){
		fputs("Error:Name too long\n",stderr);
		return 1;
	}
	strcpy(books[i].name,buffer);
	printf("请输入书籍《%s》的相关信息\n",books[i].name);
	while(scanf("%s",books[i].infor)!=1) 
	{
		fputs("Error:输入有误，请重新输入\n",stderr);
		while ((c = getchar()) != EOF && c != '\n');
	}
	books[i].isblank=0;
	puts("已添加\n");
	while ((c = getchar()) != EOF && c != '\n');//清空缓存区 
	return 0;
}


int del(struct book books[]){
	int i=0;char c;
	puts("请输入书名\n");
	while(scanf("%s",books[i].name)!=1) 
	{
		fputs("Error:输入有误，请重新输入\n",stderr);
		while ((c = getchar()) != EOF && c != '\n');
	}
	while ((c = getchar()) != EOF && c != '\n');//清空缓存区 
	for(i=0;i<BSIZE;i++){
		if(books[i].isblank==1)continue;
		if(!strcmp(books[i].name,buffer)){
			books[i].isblank=1;
			break;
		} 
	}
	if(i==BSIZE){
		fputs("找不到指定书名\n",stderr);
		return 1;
	}
	puts("已删除\n");
	return 0;
}


void read(struct book target[]){
	int i=0;FILE *fp;
	if((fp=fopen("library","r"))==NULL){
		fprintf(stderr,"Error:打开文件失败\n");
		exit(-1);
	}
	while(fscanf(fp,"%s",buffer)==1&&i<BSIZE){
		if(strcmp(buffer,"book"))continue;
		fscanf(fp,"%s",target[i].name);
		printf("读取图书《%s》\n",target[i].name);
		fgets(target[i].infor,100,fp);
		target[i].isblank=0;
		i++;
	}
	fclose(fp);
	puts("数据读入成功\n");
}


void print(struct book target[]){
	int i=0;
	puts("查找中"); 
	while(i<BSIZE){
		if(target[i].isblank==0){
		printf("book《%s》：%s\n",target[i].name,target[i].infor);
		}
		i++;
	}
	puts("全部图书已显示\n");
	
}


void save(struct book target[]){
	int i=0;FILE *fp;
	if((fp=fopen("library","w"))==NULL){
		fprintf(stderr,"Error:打开文件失败\n");
		exit(-1);
	}
	while(i<BSIZE){
		if(target[i].isblank==0){
			fprintf(fp,"book %s %s\n",target[i].name,target[i].infor);
		}
	i++;
	}
	puts("已保存\n");
	fclose(fp);
}



