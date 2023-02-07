#ifndef Portfolio_hpp
#define Portfolio_hpp

#include <stdio.h>
#include <iostream>
#include <numeric>
#include <cmath>
#include <string>
#include <vector>
#include <Eigen/Dense>

using namespace std;
using Eigen::MatrixXd;
using Eigen::Matrix2Xd;
using Eigen::VectorXd;

class Asset{
    string name;
    double r_avg;
    double sigma;

public:
    Asset(string s, double avg, double sg):name(s), r_avg(avg), sigma(sg){}
    string get_name(){return name;}
    double get_avg(){return r_avg;}
    double get_sigma(){ return sigma; }
    void Print();
//    void average_return();
//    void standard_deviation();
    ~Asset(){}
};


class Portfolio{
    vector<Asset> assets;
    VectorXd weights;
    MatrixXd cov;
public:
    Portfolio(){}
    void addAsset(Asset a);
    size_t getSize(){
	    return assets.size();
    }
    void Covariance_Matrix(MatrixXd corr);
    void Print();
    void Proximation(double rp,int flag);
    double minimumVolatility();
};

#endif /* Portfolio_hpp */
