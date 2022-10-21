#include<stdio.h>


int main(int argc,char *argv[]){
	if(argc<2)printf("Error%s",argv[0]);
	else{
		int i;
		for(i=argc;i>1;i--){
			printf("%s",argv[i-1]);
		}
	}
	return 0;
}
