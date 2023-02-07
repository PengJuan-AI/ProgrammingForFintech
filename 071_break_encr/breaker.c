#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MaxStr 500
int arrayMax(int * array, int n) {
    int Max=0;
    int index=-1;
    
    if((array==NULL)||(n==0)){
        exit(EXIT_FAILURE);
    }
    else{
        //Max = array[0];
        for(int i=0;i<n;i++){
            if (Max<array[i]) {
                Max = array[i];
                index=i;
            }
        }
    }
        
   return index;
    
}

char count_words(FILE * f){
    
    int k,max= 0;
    int index=0;
    int max_index=0;
    //int count = 1;
   // int count[26]={0};
    int array[26]={0};
    char c=' ';
    char ch=' ';

    while ((c=fgetc(f))!=EOF) {
	//char *pos=strchr(array, c);
	if ( (c==' ')||(!isalpha(c))||(c=='\n') ) {
            //count_array[i] = 0;
            continue;
        }
        else{
//		printf("%d ",index);
		index=c-'a';
            	array[index]++;
	}
    }
	max_index=arrayMax(array, 26);
    	if(max_index<0){
		exit(EXIT_FAILURE);
	}else{
		ch = 'a'+max_index;
    		max = array[max_index];
	}
		/*
            char *pos=strchr(array, left);
            if(pos==NULL){
                for(j=i;j<n-1;j++){
                    char right=tolower(str[j+1]);
                    if(left==right){
                        count++;
                    }
                }
                if(count>max){
                    max = count;
                    ch = left;
                    max_index = index;
                }
                array[index]=left;
                count_array[index] = count;
                count = 1;
                index++;
            }else{
                continue;
            }
	}
	*/
 
   // count_array[i]= '\0';
    for(k=0;k<26;k++){
        if((array[k]==max)&&(k!=max_index)){
            exit(EXIT_FAILURE);
        }
    }
    return ch;
}
//
void decrypt(FILE * f){

    //printf("%s\n",str);
    char ch_as_e = count_words(f);
    if(ch_as_e==' '){
	    exit(EXIT_FAILURE);
    }
    //printf("%c\n", ch_as_e);
    
    int e;
    int en;
    e = 'e'-'a';
    en = ch_as_e-'a';
    int key = en - e%26;
    
    if(key<0){
        key += 26;
    }
    printf("%d\n",key);

}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr,"Usage: decrypt key inputFileName\n");
    return EXIT_FAILURE;
  }
  
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  decrypt(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
