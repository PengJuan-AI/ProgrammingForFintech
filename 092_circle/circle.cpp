#include"circle.hpp"
#include <cmath>
#include <cstdio>

void Circle::move (double dx, double dy){
	this->point.move(dx,dy);
}

double Circle::intersectionArea(const Circle & otherCircle){
	//double d = std::sqrt(std::pow(otherCircle.point.x-this->point.x,2)+std::pow(otherCircle.point.y-this->point.y,2));
	double d = this->point.distanceFrom(otherCircle.point);
	//std::printf("%.2f\n", d);
	if(d<(this->radius+otherCircle.radius))
	{
		double a = this->radius*this->radius;
		double b = otherCircle.radius*otherCircle.radius;

		double d1 = (a-b+d*d)/(2*d);
		double d2 = d-d1;
		//double y = std::sqrt(a-(x*x));
		if(d<=std::abs(this->radius-otherCircle.radius))
		{
			if(this->radius<otherCircle.radius){
				return M_PI*a;
			}else{
				return M_PI*b;
			}
		}
		return a*std::acos(d1/this->radius)-d1*std::sqrt(a-d1*d1)+b*std::acos(d2/otherCircle.radius)-d2*std::sqrt(b-d2*d2);
		//return a*std::asin(y/this->radius)+b*std::asin(y/otherCircle.radius)-y*(x+std::sqrt(x*x+b-a));

	}
	return 0.0;
}
