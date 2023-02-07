#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define line 10
#define column 10

void printMatrix(char matrix[line][column]){
    for (int i=0; i<line; i++) {
        for (int j=0; j<column; j++) {
            printf("%c ",matrix[i][j]);
        }
        printf("\n");
    }
}
void initial_matrix(FILE * f, char matrix[line][column]){
    int i=0;
    int j=0;
    int c=' ';
//    int count=0;
	
    //printf("In initial\n");
    
    while((c=fgetc(f))!=EOF){
        
	if((c=='\n')||(c=='\0')){ 
		if((j>10)||(i>10)){
			fprintf(stderr,"There are extra line/characters\n");
			exit(EXIT_FAILURE);
		}
		else if(j<9)
		{
			fprintf(stderr,"There are not 10 characters\n");
			exit(EXIT_FAILURE);  
		}else{
			i++;
			j=0;
		}
	}
        else{    
	  	    matrix[i][j]=c;
		    j++;
            }
    }
    //printf("%d, %d\n",i,j);
    // Invalid input
    if(!((i==10)&&(j==0))){
	fprintf(stderr,"There are not enough line\n");
	exit(EXIT_FAILURE);  
    }

    //printMatrix(matrix);
}

void rotate_Matrix(char Matrix[line][column]){
    char b[line][column]={0};

    for (int i=0; i<line; i++) {
        for (int j=0; j<column; j++) {
            b[i][j]=Matrix[9-j][i];
            printf("%c", b[i][j]);
        }
        printf("\n");
    }

}

int main(int argc, const char * argv[]) {
    if (argc != 2) {
    fprintf(stderr,"Usage: rotate_Matrix inputFileName\n");
    return EXIT_FAILURE;
  }
	//printf("%s\n",argv[1]); 
	FILE * f = fopen(argv[1], "r");
  	if (f == NULL) {
    		perror("Could not open file");
    		return EXIT_FAILURE;
  	}
	else{
//              printf("Open\n");
                char matrix[line][column]={0};
                initial_matrix(f, matrix);
                rotate_Matrix(matrix);
        }
  
  	if (fclose(f) != 0) {
    		perror("Failed to close the input file!");
    		return EXIT_FAILURE;
  	}
	
  	return EXIT_SUCCESS;
   
}

