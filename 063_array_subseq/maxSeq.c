#include <stdio.h>
#include <stdlib.h>


size_t  maxSeq(int * array, size_t n){
    int sub=0;
    int max_sub=0;
    
    if(n==0){
        return max_sub;
    }
    for(int i=0; i<n; i++){
        if(i==0){
            sub++;
        }
        else{
            if(array[i]>array[i-1]){
                sub++;
            }else{
                if(sub>max_sub){
                    max_sub=sub;
                }
		sub=1;
            }
        }
        if((i==n-1)&&(sub>max_sub)){
            max_sub=sub;
        }
    }
    
    return max_sub;
}
