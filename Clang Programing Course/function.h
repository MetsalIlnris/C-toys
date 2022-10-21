#include"basic.h"



void add(void){
	guest *now=pguest;
	estate *finder=pestate;
	char c;
	if(now!=NULL)while(now->next!=NULL)now=now->next;
	now=newnode_guest(now);
	puts("请输入客户的电话");
	if(scanf("%s",now->p_number)!=1){
		WARN;
	}
	while ((c = getchar()) != EOF && c != '\n');//清空缓存区 
	puts("请输入客户的姓名");
	if(scanf("%s",now->name)!=1){
		WARN;
	}
	while ((c = getchar()) != EOF && c != '\n');//清空缓存区 
	puts("请输入与客户通话的次数");
	if(scanf("%d",&now->call_number)!=1){
		WARN;
	}
	while ((c = getchar()) != EOF && c != '\n');//清空缓存区 
	puts("请输入最后一次与客户通话的时间(年月日用空格隔开，如：2020 12 31)");
	if(scanf("%d %d %d",&now->last_call[0],&now->last_call[1],&now->last_call[2])!=3){
		WARN;
	}
	while ((c = getchar()) != EOF && c != '\n');//清空缓存区 
	get_guest_order(now);
	printf("保存新客户%s成功",now->name);
	while ((c = getchar()) != EOF && c != '\n');//清空缓存区 
} 


void change(void){
	char ch='0',c;
	int i=0;
	guest *finder=pguest,*now;
	puts("请输入要改变信息客户的姓名\n");
	scanf("%s",buffer);
	if(pestate!=NULL){
		for(finder=pguest;(finder!=NULL);finder=finder->next)
			if(strcmp(finder->name,buffer)==0)break;
	}
	if(finder==NULL){
		puts("没有找到该客户名\n");
		while ((c = getchar()) != EOF && c != '\n');//清空缓存区 
		return;
	}
	else {
		now=finder;
		printf("找到用户：%s",finder->name);
		printf("电话%9s\n",finder->p_number);
		printf("电话次数%2d\n",finder->call_number);
		printf("上次通话时间%4d年%2d月%2d日\n",finder->last_call[0],finder->last_call[1],finder->last_call[2]);
		for(i=0;i<3;i++){
			if(now->order[i]!=0)
				printf("该买家意向房源%d:%d\n",i+1,now->order[i]);
		}
		while(ch!='q'&&ch!=EOF){
			switch (ch=show_menu_change()){
				case '1':puts("请输入客户的电话");
					if(scanf("%s",now->p_number)!=1){
						WARN;
					}
					break;
				case '2':puts("请输入与客户通话的次数");
					if(scanf("%d",&now->call_number)!=1){
						WARN;
						}
					break;
				case '3':puts("请输入最后一次与客户通话的时间(年月日用空格隔开，如：2020 12 31)");
					if(scanf("%d %d %d",&now->last_call[0],&now->last_call[1],&now->last_call[2])!=3){
						WARN;
					}
					break;
				case '4':get_guest_order(now);
					break;
				case '5':del(now);
				default:break;
			}
			while ((c = getchar()) != EOF && c != '\n');//清空缓存区
			if(ch=='5')break;
		}
		printf("修改客户%s成功",now->name);
	}
	return;
}
		
		


void source(void){
	char c;
	estate *finder=pestate;
	int token;
	if(pestate==NULL){
		puts("\nError:没有检测到任何房源\n");
	}
	struct find_flag{
		int direction;
		int f_level[2];
		int size[2];
		int price[2];
	}flag;
	puts("\n请输入查找房源范围：\n");
	puts("\n朝向：输入0-全选；1-南；2-东；3-西；4-北\n"); 
	scanf("%d",&flag.direction);
	while ((c = getchar()) != EOF && c != '\n');//清空缓存区 
	puts("\n楼层数：输入最低与最高（例：输入5 10，输出所有五到十层的房源）\n"); 
	scanf("%d %d",&flag.f_level[0],&flag.f_level[1]);
	while ((c = getchar()) != EOF && c != '\n');//清空缓存区 
	puts("\n面积：输入最低与最高（例：输入50 200，输出所有五十到两百平方米的房源）\n"); 
	scanf("%d %d",&flag.size[0],&flag.size[1]);
	while ((c = getchar()) != EOF && c != '\n');//清空缓存区 
	puts("\n价格：输入最低与最高（例：输入500 20000，输出所有500到20000元每平方米的房源）\n"); 
	scanf("%d %d",&flag.price[0],&flag.price[1]);
	while ((c = getchar()) != EOF && c != '\n');//清空缓存区 
	puts("\n查找中\n") ;
	for(finder=pestate;finder!=NULL;finder=finder->next){
		token=(finder->f_level>flag.f_level[0]&&finder->f_level<flag.f_level[1]);
		token=token&&(finder->size>flag.size[0]&&finder->size<flag.size[1]);
		token=token&&(finder->price>flag.price[0]&&finder->price<flag.price[1]);
		if(token==1){
			if(flag.direction==0||flag.direction==finder->direction)
				print_estate(finder);
		}
	}
}


void statistics(void){
	int i=0,max_sold=0,cnt=0;
	estate *now=pestate;
	while(now!=NULL){
		if(now->sold>max_sold){
			max_sold=now->sold;
			cnt++;
		}
		now=now->next;
	}
	printf("客户意向房源共%d套\n",cnt);
	for(i=max_sold;i>0;i--){
		for(now=pestate;now!=NULL;now=now->next){
			if(now->sold==i)print_estate(now);
		}
	}
}


void book(void){
	sold_estate *now=psold;
	char c;
	if(now!=NULL)while(now->next!=NULL)now=now->next;
	now=newnode_sold(now);
	puts("请输入面积");
	if(scanf("%d",&now->size)!=1){
		WARN;
	}
	while ((c = getchar()) != EOF && c != '\n');//清空缓存区 
	puts("请输入价格");
	if(scanf("%d",&now->price)!=1){
		WARN;
	}
	while ((c = getchar()) != EOF && c != '\n');//清空缓存区 
	puts("请输入成交时间(年月日用空格隔开，如：2020 12 31)");
	if(scanf("%d %d %d",&now->time[0],&now->time[1],&now->time[2])!=3){
		WARN;
	}
	while ((c = getchar()) != EOF && c != '\n');//清空缓存区 
	puts("请输入单号");
	if(scanf("%d",&now->id)!=1){
		WARN;
	}
	while ((c = getchar()) != EOF && c != '\n');//清空缓存区 
	puts("请输入客户的姓名");
	if(scanf("%s",now->name)!=1){
		WARN;
	}
	while ((c = getchar()) != EOF && c != '\n');//清空缓存区 
	puts("请输入客户的电话");
	if(scanf("%s",now->p_number)!=1){
		WARN;
	}
	while ((c = getchar()) != EOF && c != '\n');//清空缓存区 
	printf("保存新合同%d成功",now->id);
	while ((c = getchar()) != EOF && c != '\n');//清空缓存区 
}

void read(){
	int i=0,k=0;
	FILE *fp;
	puts("\n正在读取数据\n");
	
	//读取source 
	
	estate *now=pestate;
	if((fp=fopen("source.txt","r"))==NULL){
		fprintf(stderr,"Error:打开文件source.txt失败\n");
		exit(-1);
	}
	if(now!=NULL)while(now->next!=NULL)now=now->next;
	while(fscanf(fp,"%s",buffer)==1){
		if(!strcmp(buffer,"estate")){
			now=newnode_estate(now);
		}
		else{
			puts("fail on estate");
			WARN;
		}
		puts("success in estate");
		if(fscanf(fp,"%d",&now->id)!=1)
			WARN;
		printf("代号%3d ",now->id);
		if(fscanf(fp,"%d",&now->sold)!=1)
			WARN;
		printf("卖出%2d套 ",now->sold);
		if(fscanf(fp,"%d",&now->direction) !=1&&!(now->direction>0&&now->direction<5))
			WARN;
		printf("朝%s ",directions[now->direction-1]);
		if(fscanf(fp,"%d",&now->f_level) !=1)
			WARN;
		printf("%3d层 ",now->f_level);
		if(fscanf(fp,"%d",&now->size) !=1)
			WARN;
		printf("面积%6d ",now->size);
		if(fscanf(fp,"%d",&now->price) !=1&&!(now->direction>0&&now->direction<5))
			WARN;
		printf("价格%6d ",now->price);
		if(fscanf(fp,"%s",now->infor)!=1)
			WARN;
		printf("简介：%s\n\n",now->infor);
	}
	fclose(fp);
	
	//读取guest 
	
	guest *guest_now=pguest;
	if((fp=fopen("guests.txt","r"))==NULL){
		fprintf(stderr,"Error:打开文件guests.txt失败\n");
		exit(-1);
	}
	if(guest_now!=NULL)while(guest_now->next!=NULL)guest_now=guest_now->next;
	puts("yes");
	while(fscanf(fp,"%s",buffer)==1){
		if(!strcmp(buffer,"guest")){
			guest_now=newnode_guest(guest_now);
		}
		else{
			puts("fail on guest");
			WARN;
		}
		if(fscanf(fp,"%s",guest_now->p_number)!=1)
			WARN;
		printf("电话%9s\n",guest_now->p_number);
		if(fscanf(fp,"%s",guest_now->name) !=1)
			WARN;
		printf("姓名%8s\n",guest_now->name);
		if(fscanf(fp,"%d",&guest_now->call_number)!=1)
			WARN;
		printf("电话次数%2d\n",guest_now->call_number);
		if(fscanf(fp,"%d %d %d",&guest_now->last_call[0],&guest_now->last_call[1],&guest_now->last_call[2]) !=3)
			WARN;
		printf("上次通话时间%4d年%2d月%2d日\n",guest_now->last_call[0],guest_now->last_call[1],guest_now->last_call[2]);
		if(fscanf(fp,"%d %d %d",&guest_now->order[0],&guest_now->order[1],&guest_now->order[2])!=3)
			WARN;
		for(i=0;i<3;i++){
			if(guest_now->order[i]!=0)
				printf("该买家意向房源%d:%d\n",i+1,guest_now->order[i]);
		}
		putchar('\n');
	}
	
	//读取sold
	
	sold_estate *sold_now=psold;
	if((fp=fopen("sold.txt","r"))==NULL){
		fprintf(stderr,"Error:打开文件sold.txt失败\n");
		exit(-1);
	}
	if(sold_now!=NULL)while(sold_now->next!=NULL)sold_now=sold_now->next;
	while(fscanf(fp,"%s",buffer)==1){
		if(!strcmp(buffer,"sold")){
			sold_now=newnode_sold(sold_now);
		}
		else{
			puts("fail on sold");
			WARN;
		}
		if(fscanf(fp,"%d",&sold_now->size)!=1)
			WARN;
		printf("面积%2d\n",sold_now->size);
		if(fscanf(fp,"%d",&sold_now->price)!=1)
			WARN;
		printf("价格%2d\n",sold_now->price);
		if(fscanf(fp,"%d %d %d",&sold_now->time[0],&sold_now->time[1],&sold_now->time[2]) !=3)
			WARN;
		printf("成交时间%4d年%2d月%2d日\n",sold_now->time[0],sold_now->time[1],sold_now->time[2]);
		if(fscanf(fp,"%d",&sold_now->id)!=1)
			WARN;
		printf("合同单号%2d\n",sold_now->id);
		if(fscanf(fp,"%s",sold_now->name)!=1)
			WARN;
		printf("房主%s\n",sold_now->name);
		if(fscanf(fp,"%s",sold_now->p_number)!=1)
			WARN;
		printf("电话%9s\n",sold_now->p_number);
		putchar('\n');
	}
	
	fclose(fp);
	puts("\n读取成功\n") ;
}


void save(){
	int i=0;
	FILE *fp;
	
	//储存source 
	
	if((fp=fopen("source.txt","w"))==NULL){
		fprintf(stderr,"Error:打开文件失败\n");
		exit(-1);
	}
	estate *now=pestate;
	if(now!=NULL){
		fprintf(fp,"estate %d %d %d %d ",now->id,now->sold,now->direction,now->f_level);
		fprintf(fp,"%d %d %s\n",now->size,now->price,now->infor);
		while(now->next!=NULL){
			now=now->next;
			fprintf(fp,"estate %d %d %d %d ",now->id,now->sold,now->direction,now->f_level);
			fprintf(fp,"%d %d %s\n",now->size,now->price,now->infor);
		}
	}
	fclose(fp);
	
	//储存guest
	
	if((fp=fopen("guests.txt","w"))==NULL){
		fprintf(stderr,"Error:打开文件失败\n");
		exit(-1);
	}
	guest *guest_now=pguest;
	if(guest_now!=NULL){
		fprintf(fp,"guest %s %s %d ",guest_now->p_number,guest_now->name,guest_now->call_number);
		fprintf(fp,"%d %d %d ",guest_now->last_call[0],guest_now->last_call[1],guest_now->last_call[2]);
		fprintf(fp,"%d %d %d\n",guest_now->order[0],guest_now->order[1],guest_now->order[2]);
		while(guest_now->next!=NULL){
			guest_now=guest_now->next;
			fprintf(fp,"guest %s %s %d ",guest_now->p_number,guest_now->name,guest_now->call_number);
			fprintf(fp,"%d %d %d ",guest_now->last_call[0],guest_now->last_call[1],guest_now->last_call[2]);
			fprintf(fp,"%d %d %d\n",guest_now->order[0],guest_now->order[1],guest_now->order[2]);
		}
	}
	fclose(fp);
	
	//储存sold 
	
	if((fp=fopen("sold.txt","w"))==NULL){
		fprintf(stderr,"Error:打开文件失败\n");
		exit(-1);
	}
	sold_estate *sold_now=psold;
	if(sold_now!=NULL){
		fprintf(fp,"sold %d %d %d %d %d ",sold_now->size,sold_now->price,sold_now->time[0],sold_now->time[1],sold_now->time[2]);
		fprintf(fp,"%d %s %s\n",sold_now->id,sold_now->name,sold_now->p_number);
		while(sold_now->next!=NULL){
			sold_now=sold_now->next;
			fprintf(fp,"sold %d %d %d %d %d ",sold_now->size,sold_now->price,sold_now->time[0],sold_now->time[1],sold_now->time[2]);
			fprintf(fp,"%d %s %s\n",sold_now->id,sold_now->name,sold_now->p_number);
			
		}
	}
	fclose(fp);
	
	puts("\n保存成功\n");
}



void Auto_save_change(){
	if(Auto_save_mode==true){
		Auto_save_mode=false;
	}
	else Auto_save_mode=true;
}
	
