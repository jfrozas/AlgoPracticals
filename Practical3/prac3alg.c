/*ALGORITHMS - PRACTICAL 2: SELECTION AND SHELL SORT
 * 
 * By:
 * - Javier Fernández Rozas		j.frozas
 * - Pelayo Vieites Pérez		pelayo.vieites.perez
 * 
 * Date: 21 Oct 2021		//UPDATE
 * Group: 6.1
 * 
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

#define K 1000
#define BOUND_STRING_SIZE 15
#define THRESHOLD 100

void ins_sort(int v[], int n);
void quick_sort(int v[], int n);
void ascending_init(int v[], int n);
void descending_init(int v[], int n);
void random_init(int v[], int n);

typedef void (*myFuncDef)(int *, int);

struct INITIALIZATION{
	char* name;
	myFuncDef function;
} ;

struct ALGORITHM{
	char* name;
	myFuncDef function;
} ;

double microseconds() { /* obtains the system time in microseconds */
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}


void init_seed() {
    srand(time(NULL));
/* set the seed of a new sequence of pseudo-random integers */
}


void random_init(int v [], int n) {
    int i, m=2*n+1;
    for (i=0; i < n; i++)
        v[i] = (rand() % m) - n;
/* generate pseudo-random numbers between -n and +n */
}

void ascending_init(int v [], int n) {
	for (int i=0; i < n; i++)
		v[i] = i;
}

void descending_init(int v [], int n) {
	int i, j=n;
	for (i=0; i <n; i++){
		v[i] = j;
		j--;
	}
}

void print_array(int v[], int n){
    int i;
    printf("[");
    for (i=0; i<n; i++)
        printf("%3d", v[i]);
    printf(" ]");
}

bool isSorted1(int v[], int n){
	bool sorted=true;
	int i=0;
	while (sorted && i<n-1){
		if (v[i]>v[i+1])
			sorted=false;
		i++;
	}
	return sorted;
}

//Insertion sort:
void ins_sort (int v [], int n){
	int i, x, j;
	for (i=1; i<n; i++){
		x=v[i];
		j=i-1;
		
		while(j>=0 && v[j] > x){
			v[j+1] = v[j];
			j=j-1;
		}
		v[j+1] = x;
	}
}


//Quick sort:

void swap(int v[], int a, int b){	
	//swap v, a, b interchanges values in positions a and b
	//PreCD: a and b are valid positions in the array
	int aux = v[a];
	v[a] = v[b];
	v[b] = aux;
	//as the vector is a pointer, it is already updated
}

void median3 (int v[], int i, int j){	
	
	int k = (i+j)/2;	//int k = n/2; //i=0, j=n-1 (CHECK)
	if (v[k] > v[j])	swap (v, k, i);

	if (v[k] > v[i])	swap(v,k,i);
	
	if (v[i] > v[j])	swap (v,i,j);
	
	//Now the median is in position i
}

void sortAux (int v[], int left, int right){
	int pivot, i, j;
	
	if (left+THRESHOLD <= right){
		median3(v, left, right);
		pivot = v[left];
		i = left;
		j = right;
		do
		{
			do
			{
				i++;
			} while (v[i]<pivot);
			do
			{
				j--;
			} while (v[j]>pivot);
			
			swap(v, i, j);
			
		} while (j>i);
		swap(v, i, j); //Undo last swap
		
		swap (v, left, j);
		
		sortAux (v,left, j-1);
		sortAux (v, j+1, right);
	}	
}


void quick_sort(int v[], int n){
	sortAux(v, 0, n-1);
	
	if (THRESHOLD > 1)
		ins_sort (v,n);
}

// End quicksort

void test(char* algo, char* init, int n, struct ALGORITHM A[], 
			struct INITIALIZATION I[]){
	int v[n];
	myFuncDef initFunction, algoFunction;
	//Get function pointers
	for (int j = 0; I[j].name!=NULL; j++){
		if (!strcmp(I[j].name, init)){
			initFunction = I[j].function;
			break;
		}
	}
	for (int j = 0; A[j].name!=NULL; j++){
		if (!strcmp(A[j].name, algo)){
			algoFunction = A[j].function;
			break;
		}
	}
	
	printf("\n%s sort with %s initialization\n", algo, init);
	(initFunction)(v,n);
	bool isSorted = isSorted1(v,n);
	
	print_array(v,n);
    printf("\nSorted? %d\n", (isSorted)? 1: 0);
    
    (algoFunction)(v,n);
	print_array(v,n);
	isSorted = isSorted1(v,n);
	printf("\nSorted? %d\n", (isSorted)? 1: 0);
		

}

void calculateTimes(char* algo, char* init, float underestimated,
					float tight, float overestimated, 
					struct ALGORITHM A[], struct INITIALIZATION I[]){
	int n;
	double time_a, time_b, time_1, time_2, time_T;

	printf("%s initialization. %s sort", init, algo);
	if (!strcmp(algo,"Quick")) printf(". Threshold = %d\n", THRESHOLD);
	else printf("\n");
	
	char underString[BOUND_STRING_SIZE], tightString[BOUND_STRING_SIZE], 
		overString[BOUND_STRING_SIZE];
		
	sprintf(underString, "t(n)/n^%1.2f", underestimated);
	sprintf(tightString, "t(n)/n^%1.2f", tight);
	sprintf(overString, "t(n)/n^%1.2f", overestimated);
	printf("%10s%18s%15s%15s%15s\n", "Array length", "t(n)",
	underString, tightString, overString);
	
	myFuncDef initFunction, algoFunction;
	
	//get function pointers (algorithm + initialization)
	for (int j = 0; I[j].name!=NULL; j++){
		if (!strcmp(I[j].name, init)){
			initFunction = I[j].function;
			break;
		}
	}
	for (int j = 0; A[j].name!=NULL; j++){
		if (!strcmp(A[j].name, algo)){
			algoFunction = A[j].function;
			break;
		}
	}
	
	for (n=500; n<=32000; n=2*n){
		int v[n];
		
		(initFunction)(v,n);
		time_a = microseconds();
		(algoFunction)(v,n);
		time_b = microseconds();
		time_1 = time_b - time_a;
		if (time_1 < 500){
			time_a = microseconds();
			for (int i = 1; i<=K; i++){	//K=1000
				(initFunction)(v,n);
				(algoFunction)(v,n);
			}
			time_b = microseconds();
			time_1 = time_b-time_a;
			time_a = microseconds();
			for (int i = 1; i<=K; i++)	//K=1000
				(initFunction)(v,n);
			time_b = microseconds();
			time_2 = time_b - time_a;
			time_T = (time_1-time_2) / K;
			
			printf("%10d(*)%17f%15f%15f%15f\n", n, time_T, time_T/pow(n,underestimated),
			time_T/pow(n,tight), time_T/pow(n,overestimated));
		}
		else
			printf("%10d%20f%15f%15f%15f\n", n, time_1, time_1/pow(n,underestimated),
			time_1/pow(n,tight), time_1/pow(n,overestimated));
	}
	printf("\n\n");
}

int main() {
    init_seed();
	struct INITIALIZATION I[] = {
		{"Ascending", ascending_init},
		{"Descending", descending_init},
		{"Random", random_init},
		{NULL, NULL}
		
	};

	struct ALGORITHM A[] = {
		{"Insertion", ins_sort},
		{"Quick", quick_sort},
		{NULL, NULL}
		
	};
	printf( "**************************************************\n"
            "Check of the correct functioning of the algorithms\n"
	        "**************************************************\n");
    
    test("Insertion", "Ascending", 15, A, I);
    test("Insertion", "Descending", 15, A, I);
    test("Insertion", "Random", 15, A, I);
    
    test("Quick", "Ascending", 15, A, I);
	test("Quick", "Descending", 15, A, I);
    test("Quick", "Random", 15, A, I);
    
    printf("\n\n"
           "*************************************************************\n"
	       "Computation of runtimes, empirical verification of complexity\n"
	       "*************************************************************\n");
    calculateTimes("Insertion", "Ascending", 0.8, 0.9, 1.0, A, I);
    calculateTimes("Insertion", "Descending", 1.87, 2.07, 2.27, A, I);
    calculateTimes("Insertion", "Random", 1.8, 2.0, 2.2, A, I);
    
    calculateTimes("Quick", "Ascending", 0.9, 1.1, 1.3, A, I);
    calculateTimes("Quick", "Descending", 1.8, 2.0, 2.2, A, I);
    calculateTimes("Quick", "Random", 1.0, 1.15, 1.30, A, I);
    

    return 0;
}

