#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

void Printout(vector<string> s){
    vector<string>::iterator it;
    for(it=s.begin();it!=s.end();++it){
        cout<<*it<<endl;
    }
    
}

int main(int argc, char ** argv){
    if(argc<1){
        cerr<<"Usage: ./sortline"<<endl;
        return EXIT_FAILURE;
    }
    else if (argc==1){
        string line;
        vector<string> vecs;
        while (getline(cin,line)) {
//	     if((s!="\n")&&(s!=" ")){
             	vecs.push_back(line);
//		}
        }
	//sort
	sort(vecs.begin(), vecs.end());
	//SortLines(vecs);
        //print out the vector
        Printout(vecs);
	//free memory
        //exit_success
	return EXIT_SUCCESS;
    }
    else{
	for(int i=1;i<argc;i++){
	    ifstream in(argv[i]);
	    if(!in.is_open()){
		std::cerr << "Unable to open " << argv[1] << std::endl;
                return EXIT_FAILURE;
	    }
	    string line;
	    vector<string> vecs;
	    while(getline(in,line)){
		    vecs.push_back(line);
	    }
	    sort(vecs.begin(), vecs.end());
	    //SortLines(vecs);
	    Printout(vecs);
	    in.close();
	}
	return EXIT_SUCCESS;	
    }
}
