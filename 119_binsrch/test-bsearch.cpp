#include<iostream>
#include<cstdlib>
#include<math.h>
#include"function.h"

using namespace std;

int binarySearchForZero(Function<int,int> *f, int low, int high);

class CountedIntFn : public Function<int,int>{
protected:
  unsigned remaining;
  Function<int,int> * f;
  const char * mesg;
public:
  CountedIntFn(unsigned n, Function<int,int> * fn, const char * m): remaining(n),
                                                                    f(fn),
								    mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr,"Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }

};

void check(Function<int,int> * f,
           int low,
	   int high,
	   int expected_ans,
	   const char * mesg){
	unsigned max_num;
	int ans;

	if(high>low){
		max_num = log2(high-low)+1;
	}else{
		max_num = 1;
	}
	cout<<"Now its maxnum is "<< max_num <<endl;
	CountedIntFn c(max_num, f, mesg);
	
	//cout<<"Perform bsearch here:\n";
	ans = binarySearchForZero(&c, low, high);
	cout<<"expected answer is "<<expected_ans<<" and the result is "<< ans <<endl;
	if(ans==expected_ans){
		//exit(EXIT_SUCCESS);
	}else{
		fprintf(stderr, "Wrong answer!\n");
		exit(EXIT_FAILURE);
		//return EXIT_FAILURE;
	}
	//exit(EXIT_FAILURE);
}

class SinFunction : public Function<int, int> {
public:
  virtual int invoke(int arg) {
    return 10000000 * (sin(arg/100000.0) - 0.5);
  }
};

class Xsqure:public Function<int, int>{
public:
  virtual int invoke(int arg) {
	return arg*arg;
  }
};

class Xsqureplus1:public Function<int, int>{
public: 
	virtual int invoke(int arg) {
		return pow(2,arg);
	}
};

int main(){
	SinFunction f1;
	cout<<"Test func1\n";
	check(&f1, 0,150000, 52359, "error in func1");
	check(&f1, 0,52358, 52357, "error in func1");
	check(&f1, 2,5, 4, "error in func1");
	check(&f1, 52359,150000, 52359, "error in func1");
	Xsqure f2;
	check(&f2, 1,1000,1,"error in func2");
	
	Xsqureplus1 f3;
	check(&f3, -100,100, -100, "error in func3");
	
	return EXIT_SUCCESS;
}
