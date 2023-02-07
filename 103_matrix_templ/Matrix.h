#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>

//YOUR CODE GOES HERE!
template<typename T>
class Matrix {
  private:
    int numRows;
    int numColumns;
    std::vector<std::vector<T> > rows;
  public:
    Matrix(){
	    numRows = 0;
	    numColumns = 0;
	    std::vector<std::vector<T> > obj(0, std::vector<T>(0));
    	    rows = obj;
    }
    Matrix(int r, int c){
	    this->numRows = r;
	    this->numColumns = c;
	    std::vector<std::vector<T> > obj(r,std::vector<T>(c));
	    this->rows = obj;
	    
    }
    Matrix(const Matrix<T> & rhs)  {
    	    this->numRows = rhs.numRows;
   	    this->numColumns = rhs.numColumns;
	    //std::vector<std::vector<T> > obj(rhs.numRows);
	    this->rows.resize(rhs.numRows);
	    
	    for(int i=0;i<rhs.numRows;i++){
		    this->rows[i] = rhs[i];
	    }
    }
    ~Matrix(){}

    Matrix<T> & operator=(const Matrix<T> & rhs){
	    this->numRows = rhs.numRows;
	    this->numColumns = rhs.numColumns;
   //	    std::vector<T> temp(rhs.numColumns);
	    this->rows.resize(rhs.numRows);
	    for(int i=0;i<rhs.numRows;i++){
		    (*this)[i] = rhs[i];
	    }
	    return *this;
    }

    int getRows() const{return numRows; }
    int getColumns() const{ return numColumns; }
    const std::vector<T> & operator[](int index) const{
	    assert((index<numRows)&&(index>=0));
	    return rows[index];
    }

    std::vector<T> & operator[](int index){
	    assert((index<numRows)&&(index>=0));
            return rows[index];
    }
    bool operator==(const Matrix<T> & rhs) const{
	    if((numRows==rhs.numRows)&&(numColumns==rhs.numColumns)){
            	for(int i=0;i<rhs.numRows;i++){
			//if((*this)[i] == rhs[i]){
                        if(rows[i] == rhs.rows[i]){   
				continue;
                   	}else{ return false;}
		}
   	   }else{
        	   return false;
	   }
   	   return true;
    }
    Matrix<T> operator+(const Matrix<T> & rhs) const{
    	int r = this->numRows;
   	int c = this->numColumns;
	Matrix<T> obj(r,c);

	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			obj[i][j] = (*this)[i][j]+rhs[i][j];
		}
	}
	return obj;
    }
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
            s<<"[ ";
            for(int i=0;i<rhs.getRows();i++){
		    s<<"{";
                    for(int j=0;j<rhs.getColumns();j++){
                            s<< rhs[i][j];
			    if(j!=rhs.getColumns()-1){
				    s<<", ";
			    }
                    }
		    s<<"}";
		    if(i!=rhs.getRows()-1){
		    	s<<","<<std::endl;
		    }
            }
            s<<" ]";
	    return s;
}

#endif
