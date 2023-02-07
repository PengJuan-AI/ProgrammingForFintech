#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

void DropNewLine(char * str){
    int i=0;
    while (str[i]!='\0') {
        i++;
        if(str[i]=='\n'){
            str[i]='\0';
        }
    }
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
    FILE *f = fopen(fname, "r");
    char str[50];
    //char * token=" ";
    kvarray_t * kvarray=malloc(sizeof(*kvarray));
    //kvarray->length=0;
    kvpair_t * array=malloc(sizeof(*array));
    int sz=0;
  
    while(fgets(str, sizeof(str), f)){
        DropNewLine(str);
        
        sz++;
        array=(kvpair_t *)realloc(array, sz*sizeof(kvpair_t));
        //array[sz-1].key = malloc(sizeof(char *));
        //array[sz-1].value = malloc(sizeof(char *));
        
	char * pos = strchr(str,'=');
	int len_key = (int)(pos-str);
	int len = strlen(str);
	int len_value = len-len_key-1;
        //token = strtok(str, "=");
        array[sz-1].key = strndup(str, len_key);
        //strcpy(array[sz-1].value,token);
	array[sz-1].value = strndup(pos+1, len_value);    
     //   printf("%s, %s", array[sz-1].key, array[sz-1].value);
    }
    
    kvarray->array = (kvpair_t *)malloc(sz*sizeof(kvpair_t));
    for(int i=0;i<sz;i++){
    	kvarray->array[i].key=strdup(array[i].key);
	kvarray->array[i].value=strdup(array[i].value);
    }
    kvarray->length=sz;
    for(int j=0;j<sz;j++){
	    free(array[j].key);
	    free(array[j].value);
    }
    free(array);
    fclose(f);
    
    return kvarray;
  //
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  int sz=pairs->length;
  for(int i=0;i<sz;i++){
	  free(pairs->array[i].key);
	  free(pairs->array[i].value);
  }
  free(pairs->array);
    free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  int sz = pairs->length;
    for(int i=0;i<sz;i++){
        printf("key = '%s' value = '%s'\n", pairs->array[i].key,pairs->array[i].value);
    }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  int sz=pairs->length;

  for(int i=0;i<sz;i++){
	  if((strcmp(pairs->array[i].key,key))==0){
		  return pairs->array[i].value; 
	  }
  }
  return NULL;
}

