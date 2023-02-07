#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  int len=strlen(inputName);
  char * outFileName = malloc((len+8)*sizeof(*outFileName));
  strcpy(outFileName, inputName);
  strcat(outFileName, ".counts");

  return outFileName;
}
