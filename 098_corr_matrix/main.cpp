#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include "asset.hpp"
using namespace std;
typedef vector<vector<double> > Matrix;

vector<string> parse(string s){
    stringstream ss(s);
    string tmp;
    vector<string> vec;
    
    while (getline(ss,tmp,',')) {
        vec.push_back(tmp);
    }
    
    return vec;
}

void Print_Matrix(Matrix & m){cout<<"[";
    for(int i=0;i<m.size();i++){
        if(i!=0){ cout<<" ";}
        for (int j=0; j<m[i].size(); j++) {
            std::cout.width(7);
            cout.precision(4);
            cout<<std::fixed<<m[i][j];
            if(j!=m.size()-1){ cout<<","; }
        }
        if(i!=m.size()-1){ cout<<endl; }
    }
        cout<<"]"<<endl;
}

//Calculate the covariance matrix
Matrix covariance(vector<Asset> & a, int span){
    // initialise covariance matrix
    size_t n = a.size();
    Matrix covar(n, vector<double>(n,0));
    //Calculate multiply sum of assets
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            double sum=0;
            for (int k=0; k<span-1; k++) {
                sum += (a[i].get_ror()[k]-a[i].get_avg())*(a[j].get_ror()[k]-a[j].get_avg());
            }
            covar[i][j] = sum/(span-1);
            covar[j][i] = covar[i][j];
        }
    }
    
    return covar;
}

//calculate the correlation matrix
void correlation(vector<Asset> a, Matrix & covar){
    //initialise correlation matrix
    size_t n = a.size();
    Matrix corr(n, vector<double>(n,0));
    //
    for(int i=0;i<n;i++){
        double s_a = a[i].get_sigma();
        for (int j=i; j<n; j++) {
            if(j==i){
                corr[i][j] = 1.0;
            }else{
                double s_b = a[j].get_sigma();
                corr[i][j] = covar[i][j]/(s_a*s_b);
                corr[j][i] = corr[i][j];
            }
        }
    }
    Print_Matrix(corr);
}
bool check_filename(string s){
	if(s.find(".csv")==string::npos){
		return false;
	}
	else{
		return true;
	}
}


int main(int argc, const char * argv[]) {
    // insert code here...
    if (argc!=2) {
        cerr<<"Usage: ./correlation samplefile"<<endl;
        return EXIT_FAILURE;
    }
    //read file and print out the asset
    if(!check_filename(argv[1])){
	cerr<<"Filename is invalid."<<endl;
	    return EXIT_FAILURE;
    }
    
    ifstream in;
    in.open(argv[1]);
    //ifstream in("test2.txt");
    if(!in.is_open()){
        std::cerr << "Unable to open " << argv[1] << std::endl;
        return EXIT_FAILURE;
    }
    
    string line;
    vector<Asset> assets;
    int tag=0;
    vector<double> p0;
    vector<string> s;
    int timespan = 0;
    
    while (getline(in, line)) {
        if (tag==0) {
            // Title and asset names
            s = parse(line);
            for (int i=1; i<s.size(); i++) {
                Asset a(s[i]);
                assets.push_back(a);
            }
            tag=1;
        }else if (tag==1){
            timespan = 1;
            s = parse(line);
           //check if the number of prices is correct
	    
	    if((s.size()-1)!= assets.size()){
		cerr<<"There is invalid price."<<endl;
		return EXIT_FAILURE;
	    }
	    
            for (int i=1; i<s.size(); i++) {
                if(s[i]=="null" or s[i]==" " or s[i]=="\n" or s[i]=="\t"){
                        cerr<<"The first price is valid."<<endl;
                        return EXIT_FAILURE;
                }else{
                        p0.push_back(stod(s[i]));
                }
            }
            tag=2;
        }else{
            timespan++;
            s = parse(line);
	    
	    if((s.size()-1)!= assets.size()){
                cerr<<"There is invalid price."<<endl;
                return EXIT_FAILURE;
            }
	    
            for (int i=0; i<assets.size(); i++) {
                if(s[i+1]=="null" or s[i+1]==" " or s[i+1]=="\n" or s[i+1]=="\t"){
                   // cerr<<"The first price is valid."<<endl;
                    //return EXIT_FAILURE;
                    assets[i].rate_of_return(p0[i],p0[i]);
                
                }else{
                    assets[i].rate_of_return(p0[i],stod(s[i+1]));
                    p0[i] = stod(s[i+1]);
                }
            }
        }
        //s.empty();
    }
    vector<Asset>::iterator it;
    for(it=assets.begin();it!=assets.end();++it){
        cout<<it->get_name()<<endl; //Print out asset names
        it->average_return(); //calculate average return
        it->standard_deviation(); //calculate standard deviation
    }
    Matrix c = covariance(assets, timespan);
    correlation(assets, c);
    in.close();
    return 0;
}
