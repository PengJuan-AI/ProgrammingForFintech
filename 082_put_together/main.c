#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f = fopen(filename, "r");
  counts_t * c = createCounts();
  char str[50];

  while(fgets(str,50,f)){
        int i=0;
    while (str[i]!='\0') {
        i++;
        if(str[i]=='\n'){
            str[i]='\0';
        }
    }
        char * value=lookupValue(kvPairs, str);
	addCount(c, value);
  }
  fclose(f);
  return c;
 // return NULL;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  if(argc<3){
                fprintf(stderr,"Usage: count_values key/value_pair txtFile...\n");
                return EXIT_FAILURE;
        }
        kvarray_t * kv = readKVs(argv[1]);
 //count from 2 to argc (call the number you count i)
  for(int i=2; i<argc; i++){
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
     counts_t * c = countFile(argv[i],kv);
    //compute the output file name from argv[i] (call this outName)
     char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
        if (f == NULL) {
                 perror("Could not open file");
                return EXIT_FAILURE;
        }

    //print the counts from c into the FILE f
     printCounts(c, f);
    //close f
     if (fclose(f) != 0) {
          perror("Failed to close the input file!");
          return EXIT_FAILURE;
     }
    //free the memory for outName and c
     free(outName);
     freeCounts(c);
  }

 //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
