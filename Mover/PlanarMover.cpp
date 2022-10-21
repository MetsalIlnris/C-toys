//PlanarMover

#include<cmath>
#include"PlanarMover.h"

using std::sqrt;
using std::sin;
using std::cos;
using std::atan;
using std::atan2;
using std::cout;
using std::endl;

namespace PlanarMover{
	//私有方法 
	void Mover::set_magang(){
		mag=sqrt(x*x + y*y);
		if(x == 0.0 && y == 0.0)
			ang = 0.0;
		else
			ang = atan2(y,x);
	};
	
	void Mover::set_xy(){
		x = mag *cos(ang);
		y = mag *sin(ang);
	};
	
	//构造函数 
	Mover::Mover(){
		x = y = mag = ang = 0.0;
	} 
	
	Mover::Mover(double n1,double n2,Mode form ){
		mode = form;
		if(form == RECT){
			x = n1;
			y = n2;
			set_magang();
		}
		else if(form == POL){
			mag = n1;
			ang = n2;
			set_xy();
		}
		else {
			cout<<"Incorrect 3rd argument to Mover()"<<endl;
		}
	}
	
	//重置
	void Mover::reset(double n1,double n2,Mode form){
		mode = form;
		if(form == RECT){
			x = n1;
			y = n2;
			set_magang();
		}
		else if(form == POL){
			mag = n1;
			ang = n2;
			set_xy();
		}
		else {
			cout<<"Incorrect 3rd argument to Mover()"<<endl;
		}
	}
	
	//析构函数
	Mover::~Mover(){
	} 
	
	//运算符重载
	
	Mover Mover::operator+(const Mover & b) const{
		return Mover(x + b.x,y + b.y);
	} 
	
	Mover Mover::operator-(const Mover & b) const{
		return Mover(x - b.x,y - b.y);
	}
	
	Mover Mover::operator-() const{
		return Mover(- x,- y);
	}
	
	Mover Mover::operator*(double n) const{
		return Mover(n *x,n *y);
	}
	
	double Mover::operator*(const Mover & b) const{
		return(x *b.x,y *b.y);
	}

	//友元函数 

	Mover operator*(double n,Mover & b){
		return b *n;
	}

	std::ostream & operator<<(std::ostream & os, const Mover & b){
		if(b.mode ==Mover::RECT)
			os<<"(x,y) = ("<<b.x<<","<<b.y<<")"<<endl;
		else if (b.mode ==Mover::POL)
			os<<"(mag,ang) = ("<<b.mag<<","<<b.ang<<")"<<endl;
		else
				os<<"Mover object mode is invaild";
		return os; 
	}
}
