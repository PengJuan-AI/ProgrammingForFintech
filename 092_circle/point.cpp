#include "point.hpp"

#include <cmath>
#include <cstdio>

void Point::move(double dx, double dy){
	this->x += dx;
	this->y += dy;
}

double Point::distanceFrom(const Point & p){
	double d = std::sqrt((p.x-this->x)*(p.x-this->x)+(p.y-this->y)*(p.y-this->y));
	return d;
}
