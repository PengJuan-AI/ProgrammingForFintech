#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cmath>
#include <iomanip>
#include <Eigen/Dense>
#include "Portfolio.hpp"

using namespace std;
using Eigen::MatrixXd;

//Preprocessing
vector<string> parse(string s){
    stringstream ss(s);
    string tmp;
    vector<string> vec;
    
    while (getline(ss,tmp,',')) {
        vec.push_back(tmp);
    }
    
    return vec;
}

//check if the value is numeric
bool IsNumeric(string s){
	auto it = s.begin();
	int decimal = 0;
	while(it!=s.end()){
		if(isdigit(*it)){
			it++;
		}else if(*it=='.' && decimal==0){
			//decimal point should be only one
            		it++;
            		decimal=1;
		}else if(it==s.begin()&&*it=='-'){
			//is negative
			it++;
		}
		else{
			return false;
		}
	}
	
	return !s.empty();
}

//check if each line in file is valid
//sz is the valid number of elements in a line
//n_start is the start position of numeric value
bool IsValid(vector<string> elements, size_t sz, int n_start){
	//check if it contains sz elements
	if(elements.size()!=sz){
		return false;
	}
	if(elements[0].length()==0){
		cerr<<"Please enter valid asset name."<<endl;
		exit(EXIT_FAILURE);
	}
	//the following shoud be numeric value
	for(size_t i=n_start;i<sz;i++){
		if(!IsNumeric(elements[i])){
			return false;
		}
	}

	return true;
}

int main(int argc, const char * argv[]){
	int restricted;
	int file;
	string op_restricted="-r";

	//cout << argc<<endl;
	if(argc==3){
		restricted = 0;
		file = 1;
		//cout<<"Unrestricted efficient frontier"<<endl;
	}else if(argc==4){
		if(op_restricted.compare(argv[1])==0){
			restricted = 1;
			file=2;
		//	cout<<"Restricted eff_frontier"<<endl;
		}else{
			cerr<<"Unrecognized option."<<endl;
			return EXIT_FAILURE;
		}
		//cout<<"Restricted efficient frontier"<<endl;
	}else{
		fprintf(stderr, "Usage: ./efficient_frontier (-r)  universe.csv relation_matrix.csv");
        return EXIT_FAILURE;
	}

	string line;
	vector<string> parsed; //line after being parsed
	Portfolio p;
	
	ifstream in1(argv[file]);
        if(!in1.is_open()){
                cerr << "Unable to open " << argv[file] << std::endl;
                return EXIT_FAILURE;
        }

	while(getline(in1,line)){
		parsed = parse(line); //process each line in assets file
		if(IsValid(parsed,3,1)){
			Asset a(parsed[0],stod(parsed[1]), stod(parsed[2]));
			p.addAsset(a);
		}else{
                        cerr<<"Line in universe file is unvalid!"<<endl;
                        return EXIT_FAILURE;
                }
	}
//	p.Print();
	
	ifstream in2(argv[file+1]);
        if(!in2.is_open()){
                cerr << "Unable to open " << argv[file+1] << std::endl;
                return EXIT_FAILURE;
        }
	size_t n = p.getSize();
	MatrixXd corr(n,n);
	size_t row=0;
        while(getline(in2,line)){
		if(row==n){
                        cerr<<"Too many infomation in correlation file"<<endl;
                        return EXIT_FAILURE;
                }

		parsed = parse(line);
		if(IsValid(parsed,n,0)){
			for(size_t i=0;i<n;i++){
				//cout<<stod(parsed[i]);
				corr(row,i) = stod(parsed[i]);
			}
		}else{
			cerr<<"Line in correlation file is unvalid!"<<endl;
			return EXIT_FAILURE;
		}
		row++;
	}
	//check if correlation file is incomplete
	if(row<n){
		cerr<<"Too less infomation in correlation file"<<endl;
		return EXIT_FAILURE;
	}
	//cout<<corr<<endl;
	//calculate the covariance matrix
	p.Covariance_Matrix(corr);

	//calculate minimum volatility from 1% TO 26%
	double rp;
	cout<<"ROR,volatility"<<endl;
	for(rp=0.01;rp<0.27;rp+=0.01){
		p.Proximation(rp,restricted);
		double volatility = p.minimumVolatility();
		cout<<fixed;
		cout<<setprecision(1)<<rp*100<<"%"<<",";
		cout<<setprecision(2)<<sqrt(volatility)*100<<"%"<<endl;
	}
	return EXIT_SUCCESS;
}

