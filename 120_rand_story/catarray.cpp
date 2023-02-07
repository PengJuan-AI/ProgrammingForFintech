#include "catarray.h"

bool catarray_t::FindCategory(category_t cat){
    vector<category_t>::iterator it;
    it = find(catlists.begin(), catlists.end(), cat);
    if(it!=catlists.end()){
        return true;
    }else{
        return false;
    }
}

void catarray_t::addNewCategory(category_t cat){
    catlists.push_back(cat);
    n_cats++;
}

int catarray_t::FindCatPos(category_t cat){
    size_t n = n_cats;
    size_t index;
    if(!FindCategory(cat)){
        return -1;
    }else{
        for(index=0;index<n;index++){
            if (catlists[index]==cat) {
                return index;
            }
        }
    }
    return index;
}

int catarray_t::FindCatPos(string catName){
    size_t n = n_cats;
    size_t index=-1;
 
    for(index=0;index<n;index++){
        if (catlists[index].getName()==catName) {
            return index;
        }
    }
    
    return index;
}

void catarray_t::addNewWord(string word, int pos){
    if(!catlists[pos].FindWord(word)){
        catlists[pos].addWord(word);
    }
}

const category_t & catarray_t::operator[](size_t index) const {
    return catlists[index];
}

category_t & catarray_t::operator[](size_t index){
    return catlists[index];
}

std::ostream & operator<<(ostream & s, const catarray_t & ca){
    s<<"Category list:"<<endl;
    size_t lst_sz = ca.getSize();
    for(size_t i=0;i<lst_sz;i++){
        s<<ca[i];
        /*
        size_t n = ca[i].getSize();
        for(int j=0; j<n;j++){
            cout
        }
         */
    }
    return s;
}

