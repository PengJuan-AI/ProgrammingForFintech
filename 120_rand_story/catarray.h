#ifndef __CATARRAY_H__
#define __CATARRAY_H__
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <ostream>
#include <cassert>

using namespace std;

struct category_tag {
  //Write code here for this struct
    string category;
    vector<string> words;
    size_t n_words;
public:
    category_tag(string name):category(name), n_words(0){}
    category_tag(string name, string word):category(name){
        words.push_back(word);
        n_words = words.size();
    }
    string getName() const { return category;  }
    size_t getSize() const {return n_words;}
    bool FindWord(string word);
    void addWord(string word);
    const string & operator[](size_t index) const;
    string & operator[](size_t  index);
    bool operator==(const category_tag & rhs);
    ~category_tag(){}
};
typedef struct category_tag category_t;

struct catarray_tag {
  //Write code here for this struct
    vector<category_t> catlists;
    size_t n_cats;
public:
    catarray_tag():n_cats(0){}
    catarray_tag(category_t cat){
        catlists.push_back(cat);
        n_cats = catlists.size();
    }
    size_t getSize() const { return n_cats; }
    bool FindCategory(category_t cat);
    void addNewCategory(category_t cat);
    int FindCatPos(category_t cat);
    int FindCatPos(string catName);
    void addNewWord(string word, int pos);
    const category_t & operator[](size_t  index) const;
    category_t & operator[](size_t index);
    ~catarray_tag(){}
};
typedef struct catarray_tag catarray_t;

std::ostream & operator<<(ostream & s, const category_t & c);
std::ostream & operator<<(ostream & s, const catarray_t & ca);

#endif
