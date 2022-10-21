#include<stdio.h>
#include<ctype.h>
#include<stdlib.h> 
#include<string.h>

#include"struct.h"


#define WARN {fputs("Error:数据格式错误\n",stderr);return;}


bool Auto_save_mode=false;
char buffer[50];
estate *pestate=NULL;
guest *pguest=NULL;
sold_estate *psold=NULL;



int string_to_int(char *p){
	//将字符串转化为int类型 
	char ch='0';int i = 0,ret = 0;
	while(ch = *(p+i)){
		if(ch=='\0')break;
		//printf("检索第%d个字符中\n",i+1);
		if(!isdigit(ch)){
			printf("error\n");
			return 0;
		}
		ret = ret*10 + (int)(ch-'0');
		i++;
	}
	printf("ret=%d\n",ret);
	return ret;
} 

estate* newnode_estate(estate *now){
	estate *newnode;
	newnode=(estate *)malloc(sizeof(estate));
	if(newnode==NULL){
		puts("newnode fail");
		exit(-1);
	}
	if(now==NULL){
		now=newnode;
		pestate=newnode;
	} 
	else {
		now->next=newnode;
		now=now->next;
	}
	now->sold=0;
	now->next=NULL;
	return now;
}

guest* newnode_guest(guest *now){
	guest *newnode;
	newnode=(guest *)malloc(sizeof(guest));
	if(newnode==NULL){
		puts("newnode fail");
		exit(-1);
	}
	if(now==NULL){
		now=newnode;
		pguest=newnode;
	} 
	else {
		now->next=newnode;
		now=now->next;
	}
	now->next=NULL;
	return now;
}

sold_estate* newnode_sold(sold_estate *now){
	sold_estate *newnode;
	newnode=(sold_estate *)malloc(sizeof(sold_estate));
	if(newnode==NULL){
		puts("newnode fail");
		exit(-1);
	}
	if(now==NULL){
		now=newnode;
		psold=newnode;
	} 
	else {
		now->next=newnode;
		now=now->next;
	}
	now->next=NULL;
	return now;
}

char show_menu_change(void){
	char ch='0',c='0'; 
	puts("\n____________________________________________________\n\n");
	puts("\n您要修改哪一项数据：\n");
	puts("1)电话      2)通话次数    3)最后一次通话时间 \n"); //add/change/source
	puts("4)意向房源  5)删除该项    q)返回\n");
	puts("______________________________________________________\n\n");
	ch=tolower(getchar());
	while ((c = getchar()) != EOF && c != '\n');//清空缓存区 
	//printf("%c %c",ch,c);
	return ch;
}

void print_estate(estate *finder){
	estate *now=finder;
	printf("代号%3d ",now->id);
	printf("卖出%2d套 ",now->sold);
	printf("朝%s ",directions[now->direction-1]);
	printf("%3d层 ",now->f_level);
	printf("面积%6d ",now->size);	
	printf("价格%6d ",now->price);
	printf("简介：%s\n\n",now->infor);
	return;
}

void del(guest *now){
	int i=0;
	guest *finder;
	estate *e_finder;
	for(i=0;i<3;i++){
//		printf("success in for i=%d\n",i);
		for(e_finder=pestate;e_finder!=NULL;e_finder=e_finder->next){
//			printf("success in for e_finder->id=%d\n",e_finder->id);
			if(e_finder->id==now->order[i]){
//				printf("id%d sold--\n",e_finder->id);
				e_finder->sold--;
				break;
			}
		}
	}
	puts("yes");
	if(pguest->next==NULL)pguest=NULL;
	else{
		for(finder=pguest;finder->next!=now;finder=finder->next);
		puts("yes");
		finder->next=now->next;	
	}
	free(now);
}

void get_guest_order(guest * now){
	estate *finder=pestate;
	char c;
	puts("请输入客户期望的房源(如有多套，最多输入三套，中间用空格隔开，最后输入\"end\"如：1 10 19 end)");
	if(scanf("%s",buffer)!=1){
		WARN;
	}
	if(!strstr(buffer,"end")){
		now->order[0]=string_to_int(buffer);
		if(pestate!=NULL){
			for(finder=pestate;finder!=NULL;finder=finder->next){
				if(finder->id==now->order[0]){
					finder->sold++;
					break;
				}
			}
		}
		if(finder==NULL){
			puts("没有找到第一次输入的房源，系统将自动忽略第一次输入\n"); 
			now->order[0]=0;
		}
		scanf("%s",buffer);
		if(!strstr(buffer,"end")){
			now->order[1]=string_to_int(buffer);
			if(pestate!=NULL){
				for(finder=pestate;finder!=NULL;finder=finder->next){
					if(finder->id==now->order[1]){
						finder->sold++;
						break;
					}
				}
			}
			if(finder==NULL){
				puts("没有找到第二次输入的房源，系统将自动忽略第二次输入\n"); 
				now->order[1]=0;
			}
			scanf("%s",buffer);
			if(!strstr(buffer,"end")){
				now->order[2]=string_to_int(buffer);
				if(pestate!=NULL){
					for(finder=pestate;finder!=NULL;finder=finder->next){
						if(finder->id==now->order[2]){
							finder->sold++;
							break;
						}
					}
				}
				if(finder==NULL){
					puts("没有找到第三次输入的房源，系统将自动忽略第三次输入\n"); 
					now->order[2]=0;
				}
			}
			else {
				now->order[2]=0;
			}
		}
		else{
			now->order[1]=0;
			now->order[2]=0;
		}
	} 
	else{
		now->order[0]=0;
		now->order[1]=0;
		now->order[2]=0;
	}
	while ((c = getchar()) != EOF && c != '\n');//清空缓存区 
} 
