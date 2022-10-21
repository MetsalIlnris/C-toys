#include<stdbool.h>

#define NSIZE 10
#define PSIZE 15
#define ISIZE 40
#define SSIZE 20

char *directions[4]={"南","东","西","北"};

typedef struct estate_temp{
	int id;
	int sold;
	int direction;
	int f_level;
	int size;
	int price;
	struct estate_temp *next;
	char infor[ISIZE];
}estate;

typedef struct guest_temp{
	char p_number[PSIZE];
	char name[NSIZE];
	int call_number;
	int last_call[3];
	struct guest_temp *next;
	int order[3];//order最大储存三个数据，0表示无数据存于此处 
}guest;


//面积、价格、售出时间、合同号、房主姓名、房主电话
typedef struct sold_temp{
	int size;
	int price;
	int time[3];
	int id;
	int name[NSIZE];
	char p_number[PSIZE];
	struct sold_temp *next;
}sold_estate;
