#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <cctype>
#include "catarray.h"

using namespace std;

string replaceWord(string type, catarray_t & cats){
    int pos;
    int used_pos = cats.FindCatPos("used");
    size_t sz;
    //if it is not digit, then find the type in catlist
    if(!isdigit(type[0])){
        pos = cats.FindCatPos(type);
        if(pos==-1){
            fprintf(stderr, "This type is not included!\n");
            exit(EXIT_FAILURE);
        }else{
            sz = cats[pos].getSize();
            int r_pos = rand()%sz;
            //cout<<"replace "<<type<<" with "<<cats[pos][r_pos]<<endl;
            string word =cats[pos][r_pos];
            cats[used_pos].addWord(word);
            return word;
        }
    }else{ //if type is digit
        size_t previous = stoi(type);
        size_t sz_used = cats[used_pos].getSize();
        if (previous>sz_used) {
            //if it is out of range
            fprintf(stderr, "This type is out of range!\n");
            exit(EXIT_FAILURE);
        }else{
            //cout<<"replace "<<type<<" with "<<cats[used_pos][previous]<<endl;
            string word = cats[used_pos][sz_used-previous];
            cats[used_pos].addWord(word);
            return word;
        }
        
        
    }
    return type;
}

void paseline(string s, catarray_t & cats){
    
    char sign = '_';
    size_t pre = s.find(sign);
    string newWord;
    while(pre!=s.npos){
        size_t post = s.find(sign, pre+1);
        string type = s.substr(pre+1,post-pre-1);
        //cout<<"category: "<< type <<endl;
        newWord = replaceWord(type, cats);
        s.replace(pre, post-pre+1, newWord);
//        cout<<"replaced: "<<s<<endl;
        pre = s.find(sign, pre+newWord.size());
    }
    cout<<s<<endl;
}

void readStory(string filename, catarray_t cats){
    
    fstream in(filename);
    string line;
    if(!in.is_open()){
        std::cerr << "Unable to open " << filename << std::endl;
        exit(EXIT_FAILURE);
    }
    while (getline(in, line)) {
        paseline(line, cats);
        //replaceWord(line, seed, )
    }
}

catarray_t readWords(string filename){
    fstream in(filename);
    string line;
    if(!in.is_open()){
        std::cerr << "Unable to open " << filename << std::endl;
        exit(EXIT_FAILURE);
    }
    
    catarray_t carray;
    while (getline(in, line)) {
        size_t pos = line.find(":");
        size_t n = line.length();
        string value = line.substr(pos+1,n-pos);
        string key = line.substr(0,n-value.length()-1);
        //cout<< key << ":" << value<< endl;
        category_t cat(key, value);
        //if category is new cat.-> FindCat==-1
        if(carray.FindCatPos(cat)==-1){
            //add New Cat into catlist.-> addNewCat
            carray.addNewCategory(cat);
        }else{//not new cat
            //find the pos of existing category in catarray->FindCat!=-1
            //carray.addNewWord means add new word in exsiting category
            int pos = carray.FindCatPos(cat);
            carray.addNewWord(value, pos);
        }
    }
    //Add a category to store used word
    category_t cat("used");
    carray.addNewCategory(cat);
    
    return carray;
}

int main(int argc, const char * argv[]) {
    
    //initialize random seed

    if(!isdigit(argv[3][0])){
	    fprintf(stderr,"Please enter correct random seed!\n");
	    return EXIT_FAILURE;
    }else{
    	int seed = atoi(argv[3]);
    	srand(seed);
    }
    /*
    catarray_t catlist = readWords("words.txt");
    //cout<< catlist;
    readStory("story.txt", catlist);
    */
    if (argc!=4) {
        fprintf(stderr,"Usage: ./random_story story_template_file words_file, random_seed.\n");
	return EXIT_FAILURE;
    }
    // read story and word list files
    catarray_t catlist = readWords(argv[2]);
    readStory(argv[1], catlist);
    
    
    return EXIT_SUCCESS;
}
