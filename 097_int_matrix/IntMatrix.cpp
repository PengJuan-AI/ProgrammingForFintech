#include "IntMatrix.h"

IntMatrix::IntMatrix(){
   numRows = 0;
   numColumns = 0;
  // rows = new IntArray*;
   rows = NULL;
}
IntMatrix::IntMatrix(int r, int c) {
   this->numRows = r;
   this->numColumns = c;
   this->rows = new IntArray*[r];
   for(int i=0;i<r;i++){
	   this->rows[i] = new IntArray(c);
   }
}
IntMatrix::IntMatrix(const IntMatrix & rhs)  {
   this->numRows = rhs.numRows;
   this->numColumns = rhs.numColumns;
   this->rows =  new IntArray*[rhs.numRows];
   
   //std::cout<<"In copying\n";
   for(int i=0;i<rhs.numRows;i++){
	   this->rows[i] = new IntArray(rhs.numColumns);
	   (*this)[i] = rhs[i];
	   /*
	   for(int j=0;j<rhs.numColumns;j++){
		   this->rows[i][j] = rhs.rows[i][j];
	   }
	   */
   }
   
}
IntMatrix::~IntMatrix() {
	int r = this->numRows;
	//int c = this->numColumns;
	for(int i=0;i<r;i++){
		//delete[] rows[i]->data;
		delete this->rows[i];
	}
	delete[] this->rows;
}
IntMatrix &IntMatrix::operator=(const IntMatrix & rhs) {
   
   //std::cout<<"In operator=\n";
   //std::cout<<"Print rhs:\n";
   //std::cout<< rhs << std::endl;
   if(this!=&rhs){
	if(rows!=NULL){
		for(int i=0;i<numRows;i++){
			if(rows[i]!=NULL){
				delete[] rows[i];
			}
		}
		delete[] rows;
	}
	numRows = rhs.numRows;
	numColumns = rhs.numColumns;
        rows =  new IntArray*[rhs.numRows];

   	for(int i=0;i<rhs.numRows;i++){
	   rows[i] = new IntArray(rhs.numColumns);
	   (*this)[i] = rhs[i];
	   //std::cout<<(*this)[i]<<std::endl;
	   //this->rows[i] = temp;	   
   	}
   }
   
   return *this;
}
int IntMatrix::getRows() const {
	return numRows;
}
int IntMatrix::getColumns() const {
	return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
	assert(index<numRows);
   return *rows[index];
}
IntArray & IntMatrix::operator[](int index){
   assert(index<numRows);
   return *rows[index];
}   



bool IntMatrix::operator==(const IntMatrix & rhs) const {
   if((numRows==rhs.numRows)&&(numColumns==rhs.numColumns)){
	   for(int i=0;i<rhs.numRows;i++){
		   if((*this)[i] == rhs[i]){
			   continue;
		   }else{ return false;}
	   }
   }else{
	   return false;
   }
   return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
   assert((numRows==rhs.numRows)&&(numColumns==rhs.numColumns));
   int r = this->numRows;
   int c = this->numColumns;
   IntMatrix temp(r,c);
   
   for(int i=0;i<r;i++){
	   //IntArray *a=rows[i];
	   //IntArray *b=rhs.rows[i];
	   for(int j=0;j<c;j++){
		   int x = (*this)[i][j];
		   int y = rhs[i][j];
		   //std::cout<<x<<","<<y<<std::endl;
		   temp[i][j] = x+y;
	   }
   }

   return temp;

}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
   int r = rhs.getRows();
   s<<"[ ";
   for(int i=0;i<r;i++){
	   s<<rhs[i];
	   if(i!=r-1){
		s<<","<<std::endl;
	   }
   }
   s<<" ]";

   return s;

}
