#include "IntArray.h"
#include <assert.h>
#include <ostream>
#include <iostream>

IntArray::IntArray() {
   numElements=0;
   data = NULL;
}
IntArray::IntArray(int n) {
   numElements = n;
   data = new int[n];
  // cout<<"create array "<<n<<"\n";
}

IntArray::IntArray(const IntArray & rhs)  {
   this->numElements = rhs.numElements;
   this->data =  new int[rhs.numElements];
   std::cout<<"In Array copy\n";
   for(int i=0;i<rhs.numElements;i++){
	   this->data[i]=rhs.data[i];
   }
}
IntArray::~IntArray() {
	//std::cout<<"In ~IntArray\n";
	delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
   this->numElements = rhs.numElements;
   
   for(int i=0;i<rhs.numElements;i++){
           this->data[i]=rhs.data[i];
   }
   return *this;
}
const int & IntArray::operator[](int index) const {
   assert(index<numElements);
   
   return data[index];
}
int & IntArray::operator[](int index) {
   assert(index<numElements);
    
   return data[index];
}

int IntArray::size() const {
   return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
   if(numElements==rhs.numElements){
   	for(int i=0;i<numElements;i++){
		if(data[i]==rhs.data[i]){
			continue;
		}
		else{ return false;}
	}
   }else{
	  return false;
   } 
   return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
   if(numElements==rhs.numElements){
        for(int i=0;i<numElements;i++){
                if(data[i]==rhs.data[i]){
                        continue;
                }
                else{ return true;}
        }
   }else{
          return true;
   }
   return false;
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
   int n = rhs.size();
   
   s<<"{";
   for(int i=0;i<n;i++){
	   if(i!=n-1){ s<<rhs[i]<<", "; }
	   else{
	   	s<<rhs[i];
	   }
   }
   s<<"}";

   return s;

}
