#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>

#include"PlanarMover.h"

int main(){
	using namespace std;
	using PlanarMover::Mover;
	
	//创建输出对象
	ofstream fout;
	//创建 磁盘文件，保存输出数据
	fout.open("randwalk.txt");
	
	srand(time(0));//随机种子
	double direction;
	Mover step;
	Mover result;
	unsigned long steps = 0;
	double target;
	double dstep;
	cout<<"Enter target distance(q to quit)";
	while (cin>>target)
	{
		cout<<"Enter step lenth:";
		if(!(cin>>dstep))
			break;
		
		//使用fout对象和重定向操作符将字符串输出到文件中
		fout<<"Target Distance:"<<target<<",Step Size:"<<dstep<<endl;
		
		while(result.magval()<target){
			//需要记录每一次漫步者步进号和result值
			fout<<steps<<" : "<<result<<endl;
			direction = rand() % 628;
			step.reset(dstep,direction/100,Mover::POL);
			result = step + result;
			steps++;
		} 
		cout<<"After "<<steps<<" steps, thr mover has the following location:\n";
		cout<<result<<endl;
		
		fout<<"After "<<steps<<" steps, thr mover has the following location:\n";
		fout<<result<<endl;
		
		steps=0;
		result.reset(0.0,0.0);
		cout<<"Enter target distance(q to quit)";
	} 
	
	cout<<"Quiting";
	cin.clear();
	while(cin.get() != '\n')continue;
	return 0;
}
