#include<iostream>
#include<cstdio>
#include<cctype>
#include<fstream>
#include<string>
#include<cstring>

#define SIZE 10

template<typename T>T max(T a[],int n);
template<>char* max(char* a[],int n);

int main(){
	int arr[5]={1,2,4,7,3};
	std::cout<<max(arr,5);
	const char* arr2[4]={"undertale","homeworld","eden","spaceprogram"};
	std::cout<<max(arr2,4);
}

template<typename T>
T max(T a[],int n){
	int i;T ret=a[0];
	for(i=1;i<n;i++){
		ret=ret>a[i]?ret:a[i];
	}
	return ret;
}
template<>
char* max(char* a[],int n){
	int i;char* ret=a[0];
	for(i=1;i<n;i++){
		ret=strlen(ret)>strlen(a[i])?ret:a[i];
	}
	return ret;
}





