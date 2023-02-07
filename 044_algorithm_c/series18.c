#include <stdio.h>
#include <stdlib.h>

void series18(int n){
    int x = n*(-n);
    
    for(int i=1; i<n*3+1; i++)
    {
        printf("%d",x);
        if(i!=n*3+1){
            printf(" ");
        }
        x = x+(i*2-1);
    }
	printf("\n");    

}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("N not specified\n");
        printf("usage: series18 N\n");
        return 1;
   }
    int n = atoi(argv[1]);
    series18(n);
    return 0;
}
