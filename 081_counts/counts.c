#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * counts=malloc(sizeof(*counts));
  counts->array=NULL;
  counts->sz=0;
  return counts;
}
int IsNULL(const char * name){
    if(name==NULL){
        return 1;
    }else{
        return 0;
    }
}
void appendNewName(counts_t * c, const char * name){
    int n = c->sz;
    if(n==0){
        c->array=(one_count_t *)malloc(sizeof(one_count_t));
        c->array[n].num=1;
    }else{
        c->array=(one_count_t *)realloc(c->array, (n+1)*sizeof(one_count_t));
        c->array[n].num=1;
    }
   // c->array[n].name = malloc(sizeof(char*));
    //strcpy(c->array[n].name,name);
    c->array[n].name = strdup(name);
    c->sz++;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  int i=0;
    if (IsNULL(name)) {
        name="<unknown>";
    }
    if (c->sz==0) {
        appendNewName(c, name);
    }else{
        for (i=0; i<c->sz; i++) {
            if (strcmp(c->array[i].name,name)==0) {
                c->array[i].num++;
                break;
            }
        }
        // If name is new name.
        if (i>=c->sz) {
            appendNewName(c, name);
        }
    }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  int n = c->sz;
    int index_NULL=-1;
    
    for(int i=0;i<n;i++){
        if (strcmp(c->array[i].name,"<unknown>")==0) {
            index_NULL = i;
        }else{
            fprintf(outFile, "%s: %d\n", c->array[i].name, c->array[i].num);
        }
    }
    //print count for NULL
    if (index_NULL>0) {
        fprintf(outFile, "%s: %d\n", c->array[index_NULL].name, c->array[index_NULL].num);
    }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  int n = c->sz;
  
    for (int i=0; i<n; i++) {
        free(c->array[i].name);
    }
    
    free(c->array);
    free(c);
}
