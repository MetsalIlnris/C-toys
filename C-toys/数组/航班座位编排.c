#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define fleet_SIZE 20
#define NSIZE 10

struct f_seat{
	int id;
	_Bool isblank;
	char name[NSIZE];
}; 

struct flight{
	char name[NSIZE];
	int s_amount;//s_amount为0表示航班不存在 
	int empty;
	char infor[50];
	struct f_seat *seats;
}fleet[fleet_SIZE];



char buffer[50];

char show_menu_main(void);
int choose(void);
char show_menu_miner(int i);
int add(void);
int del(void);
void read(void);
void save(void);
	
int main(void){
	puts("程序加载中");
	int i=0;char ch;
	for(i=0;i<fleet_SIZE;i++){
		fleet[i].s_amount=0;
		//strcpy(fleet[i].infor,"None");
	}
	while(ch!='q'&&ch!=EOF){
		switch (ch=show_menu_main()){
			case 'a':add();
			break;
			case 'd':del();
			break;
			case 'r':read();
			break;
			case 's':save();
			break;
			case 'c':choose();
			break;
			default:break;
		}
	}
	puts("程序结束");
	return 0; 
}


char show_menu_main(void){
	puts("\n____________________________________________________\n\n");
	puts("*****欢迎使用航班位次安排程序*****\n");
	puts("a)add增加航班    d)del删除航班       c)choose选择航班 \n"); 
	puts("s)save保存数据   r)read读入数据      q)quit退出\n"); 
	puts("______________________________________________________\n\n");
	char ch='0',c='0'; 
	ch=tolower(getchar());
	while ((c = getchar()) != EOF && c != '\n');//清空缓存区 
	//printf("%c %c",ch,c);
	return ch;
}

int choose(void) {
	int i=0,k=0;char ch,c;	struct flight *selected;
	while(i<fleet_SIZE){
		if(fleet[i].s_amount!=0){
			printf("flight %s：%s\n",fleet[i].name,fleet[i].infor);
		}
		i++;
	}
	puts("全部航班已显示\n");
	puts("\n***请输入航班名称搜索航班***\n");
	scanf("%s",buffer);
	while ((c = getchar()) != EOF && c != '\n');//清空缓存区 
	puts("查找中"); 
	for(i=0;i<fleet_SIZE;i++){
		if(fleet[i].s_amount!=0){
			if(strcmp(fleet[i].name,buffer)==0) {
				printf("find flight %s：%s\n",fleet[i].name,fleet[i].infor);
				selected=&fleet[i];
				break;
			}
		}
	}
	if(i==fleet_SIZE){
		puts("没有找到目标航班");
		return 1; 
	}

	while(ch!='q'&&ch!=EOF){
		switch (ch=show_menu_miner(i)){
			case 'b':book(selected);
			break;
			case 'c':cancel(selected);
			break;
//			case 'p':print(selected);
//			break;
//			default:break;
		}
	}
	puts("程序结束");
	return 0; 
}



char show_menu_miner(int i){
	puts("\n____________________________________________________\n\n");
	printf("flight %s 还剩%d座位\n",fleet[i].name,fleet[i].empty);
	puts("*****请操作*****\n");
	puts("   b)flight预订座位      c)cancel取消预订\n"); 
	puts("   p)print显示座位     q)quit退出\n"); 
	puts("______________________________________________________\n\n");
	char ch='0',c='0'; 
	ch=tolower(getchar());
	while ((c = getchar()) != EOF && c != '\n');//清空缓存区 
	//printf("%c %c",ch,c);
	return ch;
}


int add(void){
	int i=0,k=0;char c;
	for(i=0;i<fleet_SIZE;i++){
		if(fleet[i].s_amount==0)break;
	}
	if(i==fleet_SIZE){
		fputs("Error:Don't have enough space\n",stderr);
		return 1;
	}
	puts("请输入航班名\n");
	scanf("%s",buffer);
	while ((c = getchar()) != EOF && c != '\n');//清空缓存区 
	if(strlen(buffer)>NSIZE){
		fputs("Error:Name too long\n",stderr);
		return 1;
	}
	strcpy(fleet[i].name,buffer);
	printf("请输入航班 %s 的相关信息\n",fleet[i].name);
	while(scanf("%s",fleet[i].infor)!=1) 
	{
		fputs("Error:输入有误，请重新输入\n",stderr);
		while ((c = getchar()) != EOF && c != '\n');
	}
	printf("请输入航班 %s 的座位数量\n",fleet[i].name);
	while(scanf("%d",&fleet[i].s_amount)!=1||fleet[i].s_amount<=0) 
	{
		fputs("Error:输入有误，请重新输入\n",stderr);
		while ((c = getchar()) != EOF && c != '\n');
	}
	fleet[i].seats=malloc(sizeof(struct f_seat)*fleet[i].s_amount);//为seats分配空间 
	for(k=0;k<fleet[i].s_amount;k++){
		fleet[i].seats[k].id=k;
		fleet[i].seats[k].isblank=1;
	}
	fleet[i].empty=fleet[i].s_amount;
	puts("已添加\n");
	while ((c = getchar()) != EOF && c != '\n');//清空缓存区 
	return 0;
}


int del(void){
	int i=0;char c;
	puts("请输入航班名\n");
	while(scanf("%s",buffer)!=1) 
	{
		fputs("Error:输入有误，请重新输入\n",stderr);
		while ((c = getchar()) != EOF && c != '\n');
	}
	while ((c = getchar()) != EOF && c != '\n');//清空缓存区 
	for(i=0;i<fleet_SIZE;i++){
		if(fleet[i].s_amount==0)continue;
		if(!strcmp(fleet[i].name,buffer)){
			fleet[i].s_amount=0;//s_amount==0表示航班不存在 
			free(fleet[i].seats);
			break;
		} 
	}
	if(i==fleet_SIZE){
		fputs("找不到指定航班\n",stderr);
		return 1;
	} 
	puts("已删除\n");
	return 0;
}


void read(void){
	int i=0,k=0,cnt=0;FILE *fp;
	if((fp=fopen("flights","r"))==NULL){
		fprintf(stderr,"Error:打开文件失败\n");
		exit(-1);
	}
	while(fscanf(fp,"%s",buffer)==1&&i<fleet_SIZE){
		if(strcmp(buffer,"flight"))continue;
		fscanf(fp,"%s",fleet[i].name);
		printf("读取航班 %s \n",fleet[i].name);
		if(fscanf(fp,"%d",&fleet[i].s_amount)!=1) 
		{
			fputs("Error:数据格式错误\n",stderr);
			return;
		}
		fleet[i].empty=fleet[i].s_amount;
		fleet[i].seats=malloc(sizeof(struct f_seat)*fleet[i].s_amount);//为seats分配空间 
		for(k=0;k<fleet[i].s_amount;k++){
			printf("座位%d\n",k);
			if(fscanf(fp,"%d ",&fleet[i].seats[k].isblank)!=1) 
			{
				fscanf(fp,"%s ");
				if(cnt>3){
					fputs("Error:id数据格式错误\n",stderr);
					return;
				}
			}
			if(fleet[i].seats[k].isblank==0){
				if(fscanf(fp,"%s ",fleet[i].seats[k].name)!=1) 
				{
					fputs("Error:name数据格式错误\n",stderr);
					return;
				}
				fleet[i].empty--;
			}
		}
		fscanf(fp,"%s",fleet[i].infor);
		printf("还剩%d座位\n",fleet[i].empty);
		i++;
	}
	fclose(fp);
	puts("数据读入成功\n");
}



void save(void){
	int i=0,k=0;FILE *fp;
	if((fp=fopen("flights","w"))==NULL){
		fprintf(stderr,"Error:打开文件失败\n");
		exit(-1);
	}
	while(i<fleet_SIZE){
		if(fleet[i].s_amount!=0){
			fprintf(fp,"flight %s\n %d\n",fleet[i].name,fleet[i].s_amount);
		}
		for(k=0;k<fleet[i].s_amount;k++){
			fprintf(fp," %d ",fleet[i].seats[k].isblank);
			if(fleet[i].seats[k].isblank==0){
				fprintf(fp," %s ",fleet[i].seats[k].name);
			}
		}
		fputs(fleet[i].infor,fp);
		fputc('\n',fp);
		i++;
	}
	puts("已保存\n");
	fclose(fp);
}


int book(struct flight *selected){
	int i=0;char c;
	puts("请输入姓名\n");
	scanf("%s",buffer);
	if(strlen(buffer)>NSIZE){
		fputs("Error:Name too long\n",stderr);
		return 1;
	}
	puts("请输入你想预订的位置\n");
	while(scanf("%d", &i)!=1||i<0||i>(*selected).s_amount){
		printf("输入有误，请重新输入:");
		while ((c = getchar()) != EOF && c != '\n');
	}
	(*selected).seats[i].isblank=0;
	strcpy((*selected).seats[i].name,buffer);
	(*selected).empty--;
	puts("已预订\n");
	while ((c = getchar()) != EOF && c != '\n');//清空缓存区 
	return 0;
}

int cancel(struct flight *selected){
	int i=0;char ch,c;
	puts("请输入你预订的位置\n");
	while(scanf("%d", &i)!=1&&i<0&&i>(*selected).s_amount){
		printf("输入有误，请重新输入:");
		while ((c = getchar()) != EOF && c != '\n');
	}
//	printf("确定取消乘客-%s-的预订吗？\n",(*selected).seats[i].name);
//	ch=getchar();
//	while ((c = getchar()) != EOF && c != '\n');//清空缓存区 
//	if(ch!=1){
//		puts("取消cancel\n");
//		return;
//	}
	(*selected).seats[i].isblank=1;
	(*selected).empty++;
	puts("已取消\n");
	while ((c = getchar()) != EOF && c != '\n');//清空缓存区 
	return 0;
}
