#include "asset.hpp"

void Asset::rate_of_return(double p0, double p1){
    ror.push_back(p1/p0-1);
}

void Asset::average_return(){
    //r_avg = accumulate(ror.begin(), ror.end(), 0);
    size_t n = ror.size();
    double sum=0;
    vector<double>::iterator it;
    for(it=ror.begin();it!=ror.end();++it){
        sum += *it;
    }
    r_avg = sum/n;
}

void Asset::standard_deviation(){
    size_t n = ror.size();
    double square_sum = 0;
    vector<double>::iterator it;
    for(it=ror.begin();it!=ror.end();++it){
        square_sum += pow(*it-r_avg,2);
    }
    double re = square_sum/(n-1);
    sigma = sqrt(re);
}

