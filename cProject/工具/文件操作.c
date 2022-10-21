#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#define BUFFER_SIZE 16

int main(int argc,char *argv[]){
	FILE *fp1,*fp2; 
	char *buff,ch;
	buff=malloc(BUFFER_SIZE);
	printf("%d",argc);
	if(argc!=3){
		fprintf(stderr,"Error:参数不匹配，请输入两个参数。%s\n",argv[1]);
		exit(-1);
	}
	if((fp1=fopen(argv[1],"rb"))==NULL){
		fprintf(stderr,"Error:打开%s失败\n",argv[1]);
		exit(-1);
	}
	//实现复制 
	if((fp1=fopen(argv[2],"wb"))==NULL){
		fprintf(stderr,"Error:打开%s失败\n",argv[2]);
		exit(-1);
	}
	size_t bytes;
	while((bytes=fread(buff,sizeof(char),BUFFER_SIZE,fp1))>0){
		fwrite(buff,sizeof(char),BUFFER_SIZE,fp2);
	}
	
	//实现内容逐字符更改
	while((ch=getc(fp1))!=EOF){
		fseek(fp1,-sizeof(char),SEEK_CUR);
		putc(toupper(ch),fp1);
		//putchar(ch);
	}
	//实现文件中句子处理
	char line[BUFFER_SIZE];
	while(fgets(line,BUFFER_SIZE,fp1)!=NULL){
		char *p=line;
		while(*p!='\0'){
			p++;
		}
	}
	fclose(fp1);
	fclose(fp2);
	return 0;
}

//#define N 100
//int main() {
//    FILE *fp;
//    char str[N + 1];
//    //判断文件是否打开失败
//    if ( (fp = fopen("d:\\demo.txt", "rt")) == NULL ) {
//        puts("Fail to open file!");
//        exit(0);
//    }
//    //循环读取文件的每一行数据
//    while( fgets(str, N, fp) != NULL ) {
//        printf("%s", str);
//    }
//   
//    //操作结束后关闭文件
//    fclose(fp);
//    return 0;
//}


