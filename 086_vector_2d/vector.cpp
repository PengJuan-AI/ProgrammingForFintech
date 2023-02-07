#include "vector.hpp"

#include <cmath>
#include <cstdio>

/* write your class implementation in this file
 */
/*
void Vector2D::initVector(double init_x, double init_y){
    x = init_x;
    y = init_y;
}
*/
double Vector2D::getMagnitude() const{
    double m;
    m = std::sqrt(x*x+y*y);
    
    return m;
}

Vector2D Vector2D::operator+(const Vector2D & rhs) const{
    Vector2D newvector;
    newvector.x = x+rhs.x;
    newvector.y = y+rhs.y;
    
    return newvector;
}
Vector2D & Vector2D::operator+=(const Vector2D &rhs){
    this->x += rhs.x;
    this->y += rhs.y;
    
    return *this;
}
double Vector2D::dot(const Vector2D &rhs) const{
    return x*rhs.x+y*rhs.y;
}

void Vector2D::print() const{
    printf("<%.2f, %.2f>", x,y);
}
