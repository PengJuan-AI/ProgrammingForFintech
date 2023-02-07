#include <stdio.h>
#include <stdlib.h>

size_t  maxSeq(int * array, size_t n);

void run_test(int  * array, size_t n, size_t ans,int m){
    size_t re=maxSeq(array, n);
    if(re!=ans){
	printf("Array %d: Should be %zu but was %zu\n", m,ans, re);
        exit(EXIT_FAILURE);
    }
}

int main(void){

        int array1[]={1,2,5,8,10};
        int array2[] = {1,2,1,3,5,7,2,4,6,9};
        int array3[] = {};
        int array4[] = {1,1};
        int array5[] = {5,4,3,2,1,0};
        int array6[] = {1};
	int array7[] = {-1,-2,-3,-4,-5};
	int array8[] = {1,2,3,4,90,0,-1,2,3,6,8,12,30};

        run_test(array1, 5,5,1);
        run_test(array2, 10,4,2);
        run_test(array3, 0,0,3);
        run_test(array4, 2,1,4);
        run_test(array5, 6,1,5);
        run_test(array6, 1,1,6);
        run_test(NULL,0,0,8);
        run_test(array7, 5,1,7);
	run_test(array8, 13,7,9);

        return EXIT_SUCCESS;
}
