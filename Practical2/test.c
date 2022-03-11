#ifndef PRAC2ALG_C
#define PRAC2ALG_C

#include "prac2alg.c"

void test1() {
    int n = 17;
    int v[n];
    random_init(v,n);
    bool isSorted = isSorted1(v,n);

    printf("\nRandom initialization\n");
    print_array(v,n);
    printf("\nSorted? %d\n", (isSorted)? 1: 0);
    if (!isSorted){
    	printf("Selection sort\n");
    	sel_sort(v,n);
    	print_array(v,n);
    	isSorted = isSorted1(v,n);
    	printf("\nSorted? %d\n", (isSorted)? 1: 0);
    }
}
void test2() {
    int n = 10;
    int v[n];
    descending_init(v,n);
    bool isSorted = isSorted1(v,n);

    printf("\nDescending initialization\n");
    print_array(v,n);
    printf("\nSorted? %d\n", (isSorted)? 1: 0);
    if (!isSorted){
    	printf("Selection sort\n");
    	sel_sort(v,n);
    	print_array(v,n);
    	isSorted = isSorted1(v,n);
    	printf("\nSorted? %d\n", (isSorted)? 1: 0);
    }
}

void main(){
    
    test1();
    test2();

}

#endif