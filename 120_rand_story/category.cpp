#include "catarray.h"

bool category_t::FindWord(string word){
    vector<string>::iterator it;
    it = find(words.begin(), words.end(), word);
    if(it!=words.end()){
        return true;
    }else{
        return false;
    }
}

void category_t::addWord(string word){
    //if(FindWord(word)){
        words.push_back(word);
        n_words++;
    //}
}
const string & category_t::operator[](size_t index) const {
    assert(index<n_words);
    return words[index];
}

string & category_t::operator[](size_t index){
    assert(index<n_words);
    return words[index];
}
bool category_t::operator==(const category_t &rhs){
    if (this->category==rhs.category) {
        return true;
    }else{
        return false;
    }
}

std::ostream & operator<<(ostream & s, const category_t & c){
    s<< c.getName();
    s<<":";
    //vector<string>::iterator it;
    size_t n = c.getSize();
    for(size_t i=0;i<n;i++){
        s<<c[i]<<" ";
    }
    s<<endl;
    return s;
}

