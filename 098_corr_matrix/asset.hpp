#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <numeric>
#include <cmath>

using namespace std;

class Asset{
    string name;
    vector<double> ror;
    double r_avg;
    double sigma;

public:
    Asset(string s):name(s){}
    vector<double> get_ror(){ return ror; }
    string get_name(){return name;}
    double get_avg(){return r_avg;}
    double get_sigma(){
        return sigma;
    }
    void rate_of_return(double,double);
    void average_return();
    void standard_deviation();
    ~Asset(){}
};

