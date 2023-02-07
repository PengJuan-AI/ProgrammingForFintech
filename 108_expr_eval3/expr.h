#include <iostream>
#include <ctype.h>
#include <cstdlib>
#include <string.h>
#include <string>
#include <stdio.h>
using namespace std;

class Expression{
    public:
    virtual std::string toString() const=0;
    virtual ~Expression(){}
    string inFix(string op,Expression * lhs, Expression * rhs ) const{
        string s;
        s += "(";
        s += lhs->toString();
        s += op;
        s += rhs->toString();
        s += ")";
        
        return s;
    }
    virtual long evaluate() const = 0;
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
    virtual ~NumExpression(){}
    virtual long evaluate() const{ return num; }

};

class PlusExpression : public Expression{
    Expression *lhs;
    Expression *rhs;
    public:
    PlusExpression(Expression * lhs, Expression * rhs):lhs(lhs),rhs(rhs){}
    virtual std::string toString() const{
        return inFix(" + ", lhs, rhs);
    }
    virtual ~PlusExpression(){
    	delete lhs;
	delete rhs;
    }
    virtual long evaluate() const{
	    return lhs->evaluate()+rhs->evaluate();
    }
};

class MinusExpression : public Expression{
    Expression *lhs;
    Expression *rhs;
    public:
    MinusExpression(Expression * lhs, Expression * rhs):lhs(lhs),rhs(rhs){}
    virtual std::string toString() const{
        return inFix(" - ", lhs, rhs);
    }
    virtual ~MinusExpression(){
    	delete lhs;
        delete rhs;
    }
    virtual long evaluate() const{
            return lhs->evaluate()-rhs->evaluate();
    }
};

class TimesExpression : public Expression{
    Expression *lhs;
    Expression *rhs;
    public:
    TimesExpression(Expression * lhs, Expression * rhs):lhs(lhs),rhs(rhs){}
    virtual std::string toString() const{
        return inFix(" * ", lhs, rhs);
    }
    virtual ~TimesExpression(){
    	delete lhs;
        delete rhs;
    }
    virtual long evaluate() const{
            return lhs->evaluate()*rhs->evaluate();
    }
};

class DivExpression : public Expression{
    Expression *lhs;
    Expression *rhs;
    public:
    DivExpression(Expression * lhs, Expression * rhs):lhs(lhs),rhs(rhs){}
    virtual std::string toString() const{
        return inFix(" / ", lhs, rhs);
    }
    virtual ~DivExpression(){
        delete lhs;
        delete rhs;
    }
    virtual long evaluate() const{
            return lhs->evaluate()/rhs->evaluate();
    }
};
