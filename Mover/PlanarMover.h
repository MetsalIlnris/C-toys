#ifndef PLANARMOVER_H_
#define PLANARMOVER_H_

#include<iostream>

namespace PlanarMover{
	class Mover{
	public:
		enum Mode {RECT,POL};
		//RECT表示直角坐标，POL表示极坐标 (弧度制 
	private:
		double x;   //横坐标 
		double y;   //纵坐标 
		double mag; //向量长度 
		double ang; //向量的方向，单位为度 
		Mode mode;
		void set_magang();
		void set_xy();
		
	public:
		Mover();
		Mover(double x,double y,Mode form = RECT);
		void reset(double x = 0.0,double y = 0.0,Mode form = RECT);
		~Mover();
		double xval() const {return x;};
		double yval() const {return y;};
		double magval() const {return mag;}
		double angval() const {return ang;}
		Mover operator+(const Mover & b) const;
		Mover operator-(const Mover & b) const;
		Mover operator-() const;
		Mover operator*(double n) const;
		double operator*(const Mover & b) const;
		void polar_mode(){mode = POL;}
		void rect_mode(){mode = RECT;}
		
		friend Mover operator*(double n,Mover & b); 
		friend std::ostream & operator<<(std::ostream & os, const Mover & b);
	};
}

#endif
