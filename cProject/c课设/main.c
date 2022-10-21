#include<stdio.h>
#include<stdbool.h>
#include"function.h"



extern bool Auto_save_mode;


char show_menu_main(void);


int main(){
	puts("程序加载中");
	int i=0;char ch;
	read();
	
	while(ch!='q'&&ch!=EOF){
		switch (ch=show_menu_main()){
			case '1':add();
			break;
			case '2':change();
			break;
			case '3':source();
			break;
			case '4':statistics();
			break;
			case '5':book();
			break;
			case '6':Auto_save_change();
			break;
			case '7':read();
			break;
			case '8':save();
			break;
			default:break;
		}
	}
	puts("退出前是否保存？（保存请按一,不保存按任意键）\n"); 
	if(getchar()=='1')save();
	puts("程序结束，感谢您的使用\n");
	return 0; 
}

char show_menu_main(void){
	if(Auto_save_mode==1)save();
	puts("\n____________________________________________________\n\n");
	puts("*****欢迎使用房地产管理程序*****\n");
	puts("1)新客户登记    2)修改客户数据   3)房源数据 \n"); //add/change/source
	printf("4)统计          5)预订登记       6)%s自动保存模式\n\n",Auto_save_mode?"关闭":"开启"); //save/read/Autp_save_change
	puts("7)读取数据      8)保存数据       q)退出\n");
	puts("______________________________________________________\n\n");
	char ch='0',c='0'; 
	ch=tolower(getchar());
	while ((c = getchar()) != EOF && c != '\n');//清空缓存区 
	//printf("%c %c",ch,c);
	return ch;
}


