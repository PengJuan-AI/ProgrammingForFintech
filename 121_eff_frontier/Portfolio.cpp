#include "Portfolio.hpp"

void Asset::Print(){
    cout<< name <<":"<<endl;
    cout<< "Average return" <<r_avg <<endl;
    cout<< "Standard deviation" <<sigma <<endl;
}

void Portfolio::addAsset(Asset a){
    assets.push_back(a);
}
void Portfolio::Print(){
    vector<Asset>::iterator it;
    for(it=assets.begin();it!=assets.end();++it){
        (*it).Print();
    }
}

void Portfolio::Covariance_Matrix(MatrixXd corr){
    size_t sz = assets.size();
    cov.resize(sz,sz);

    for(size_t i=0;i<sz;i++){
        double s_a = assets[i].get_sigma();
        for(size_t j=i;j<sz;j++){
            double s_b = assets[j].get_sigma();
            cov(i,j) = s_a*s_b*corr(i,j);
                     cov(j,i) = cov(i,j);
        }
    }
//    cout<<"The covariance matrix:"<<endl;
//    cout<<cov<<endl;

}

void Portfolio::Proximation(double rp, int flag){
    size_t sz = assets.size();
    Matrix2Xd a;
    a.resize(2,sz);
    //cout<<"Restricted:"<<flag<<endl;

    for(size_t i=0;i<sz;i++){
        a(0,i)=1;
        a(1,i)=assets[i].get_avg();
    }
 
    //Zero matrix
    MatrixXd zero = MatrixXd::Zero(2,2);

    MatrixXd A(sz+2,sz+2);
    A<< cov,a.transpose(),a,zero;

    //initialize vector b
    VectorXd b(sz+2);
    Eigen::Vector2d temp(1,rp);
    b<<VectorXd::Zero(sz),temp;

    //Ax=b
    VectorXd x(sz+2);
    weights.resize(sz);
    x = A.colPivHouseholderQr().solve(b);
    weights = x(Eigen::seq(0,sz-1));
    //cout<<weights<<endl;

    VectorXd index = VectorXd::Zero(sz);
    //if it is restricted
    while(flag==1){
        vector<int> negative_i;
        //how many weight in weights is negative
        for(size_t i=0;i<sz;i++){
            if(weights(i)<0){
	//	    cout<<i<<" ";
		//if this weight is not added into A Matrix
		if(index(i)==0){
                	index(i)=1;
			negative_i.push_back(i);
		}
	    }
        }
	int negative = negative_i.size();
	//while weights still contains negative value
        if(negative!=0){
	    //cout<<endl<<"Total negative weight(s): "<<negative<<endl;
            int col = A.cols();
            int row = A.rows();
            MatrixXd R = MatrixXd::Zero(negative,col);
            for (int k=0; k<negative; k++) {
                R(k,negative_i[k])=1;
            }

            MatrixXd newZero = MatrixXd::Zero(negative,negative);
            MatrixXd tempA(row+negative, col+negative);
            VectorXd tempb(col+negative);
            tempA<<A,R.transpose(),R,newZero;
            A = tempA;
            tempb<<b, VectorXd::Zero(negative);
            b = tempb;
            //recalculate weights
            x = A.colPivHouseholderQr().solve(b);
            weights = x(Eigen::seq(0,sz-1));
	    //cout<<weights<<endl;
	    for(int j=0;j<negative;j++){
		    if(weights(j)<-pow(10,-17)){
			    weights(j)=0;
		    }
	    }
	    negative_i.empty();
        }
        else{
            break;
        }
    }
}

double Portfolio::minimumVolatility(){
//    cout<<"Weights: "<<endl;
//    cout<<weights<<endl;

    double vp;
    vp = weights.transpose()*cov*weights;
    
    return vp;

}
