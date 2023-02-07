#include <iostream>
#include <ctype.h>
#include <cstdlib>
#include <string.h>
#include <string>
#include <stdio.h>
//using namespace std;

class Expression{
	public:
	virtual std::string toString() const=0;
	virtual ~Expression(){}
};

class NumExpression: public Expression{
	long num;
	public:
	NumExpression(long n):num(n){
		//std::cout<<"In NumExpression, construct"<< n <<std::endl;
	}
	virtual std::string toString() const{ 
		std::string re = std::to_string(num);
		return re;
       	}
	virtual ~NumExpression(){
		//std::cout<<"delete "<<num<<std::endl;}
	}
};

class PlusExpression : public Expression{
	Expression *lhs;
	Expression *rhs;
	public:
	PlusExpression(Expression * lhs, Expression * rhs):lhs(lhs),rhs(rhs){}
	virtual std::string toString() const{
		std::string s;
		s += "(";
		s += lhs->toString();
		s += " + ";
		s += rhs->toString();
		s += ")";
		return s;
	}
	virtual ~PlusExpression(){
		delete lhs;
		delete rhs;
	}
};
