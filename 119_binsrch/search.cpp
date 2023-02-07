#include "function.h"
#include <iostream>
#include <math.h>

using namespace std;

int binarySearchForZero(Function<int, int> * f, int low, int high){
    int mid = (low+high)/2;
    int l = low;
    int r = high;
    
    if(low==high){ return low; }
    int max_times = log2(high-low)+1;
    int ans; 
    
    while(l<r){
	mid = (l+r)/2;
	ans = f->invoke(mid);
	if(ans>0){
		r = mid-1;
	}
	else if(ans<0){
		l = mid;
	}
	else{
		return mid;
	}
	max_times--;
	if(max_times==0){
//		if(ans>0){ return l; }
		//all negative
		cout<< "ALL negative." << endl;
   	 	if(r==high){ return high-1; }
    		//all positive
		cout << "All postive."<<endl;
    		if(l==low){ return low; }
	}
    }
    cout<< "l==r"<<endl;
   if(l==r){ return l; }
   return l; 
}

