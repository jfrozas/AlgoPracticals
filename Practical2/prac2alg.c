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

#define K 1000

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
	for (int i=0; i <n; i++){
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

//Selection sort:
void sel_sort (int v [], int n){
	int i, j, minj, minx;
	for (i=0; i<n; i++){
		minj = i;
		minx = v[i];
		for (j = i+1; j < n; j++){
			if (v[j] < minx){
				minj = j ;
				minx = v[j];
			}
		}
		v[minj] = v[i];
		v[i] = minx;
	}
}

//Shell sort:
void shell_sort (int v [], int n){
	int increment, i, tmp, j;
	bool keepgoing;
	increment = n;
	while (increment != 1){
		increment = increment/2;
		for (i=increment; i<n; i++){
			tmp = v[i];
			j = i;
			keepgoing = true;
			while (j-increment >=0 && keepgoing){
				if (tmp < v[j-increment]){
					v[j] = v[j-increment];
					j = j-increment;
				}
				else keepgoing=false;
			}
			v[j]=tmp;
		}
	}
		
}

bool isSorted1(int v[], int n){
	bool isSorted=true;
	int i=0;
	while (isSorted && i<n-1){
		if (v[i]>v[i+1])
			isSorted=false;
		i++;
	}
	return isSorted;
}

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

void test3() {
    int n = 17;
    int v[n];
    random_init(v,n);
    bool isSorted = isSorted1(v,n);

    printf("\nRandom initialization\n");
    print_array(v,n);
    printf("\nSorted? %d\n", (isSorted)? 1: 0);
    if (!isSorted){
    	printf("Shell sort\n");
    	shell_sort(v,n);
    	print_array(v,n);
    	isSorted = isSorted1(v,n);
    	printf("\nSorted? %d\n", (isSorted)? 1: 0);
    }
}
void test4() {
    int n = 10;
    int v[n];
    descending_init(v,n);
    bool isSorted = isSorted1(v,n);

    printf("\nDescending initialization\n");
    print_array(v,n);
    printf("\nSorted? %d\n", (isSorted)? 1: 0);
    if (!isSorted){
    	printf("Shell sort\n");
    	shell_sort(v,n);
    	print_array(v,n);
    	isSorted = isSorted1(v,n);
    	printf("\nSorted? %d\n", (isSorted)? 1: 0);
    }
}



void timesR_sel(){	//Selection Sort (random init)
	double time_a, time_b, time_1, time_2, time_T;
	int n;
	printf("\nRandom initialization. Selection sort\n");
	printf("%10s%18s%15s%15s%15s\n", "Array length", "t(n)",
	"t(n)/n^1.8", "t(n)/n^2", "t(n)/n^2.2");

	for (n=500; n<=32000; n=2*n){
		int v[n];
		random_init(v,n);
		time_a = microseconds();
		sel_sort(v,n);
		time_b = microseconds();
		time_1 = time_b - time_a;
		if (time_1 < 500){
			time_a = microseconds();
			for (int i = 1; i<=K; i++){	//K=1000
				random_init(v,n);
				sel_sort(v,n);
			}
			time_b = microseconds();
			time_1 = time_b-time_a;
			time_a = microseconds();
			for (int i = 1; i<=K; i++)	//K=1000
				random_init(v,n);
			time_b = microseconds();
			time_2 = time_b - time_a;
			time_T = (time_1-time_2) / K;
			
			printf("%10d(*)%17f%15f%15f%15f\n", n, time_T, time_T/pow(n,1.8),		//Added "(*)"
			time_T/pow(n,2), time_T/pow(n,2.2));
		}
		else
			printf("%10d%20f%15f%15f%15f\n", n, time_1, time_1/pow(n,1.8),
			time_1/pow(n,2), time_1/pow(n,2.2));
	}
}

void timesAsc_sel(){	//Selection Sort (ascending init)
	double time_a, time_b, time_1, time_2, time_T;
	int n;
	printf("\nAscending initialization. Selection sort\n");
	printf("%10s%18s%15s%15s%15s\n", "Array length", "t(n)",
	"t(n)/n^1.8", "t(n)/n^2", "t(n)/n^2.2");

	for (n=500; n<=32000; n=2*n){
		int v[n];
		ascending_init(v,n);
		time_a = microseconds();
		sel_sort(v,n);
		time_b = microseconds();
		time_1 = time_b - time_a;
		if (time_1 < 500){
			time_a = microseconds();
			for (int i = 1; i<=K; i++){	//K=1000
				ascending_init(v,n);
				sel_sort(v,n);
			}
			time_b = microseconds();
			time_1 = time_b-time_a;
			time_a = microseconds();
			for (int i = 1; i<=K; i++)	//K=1000
				ascending_init(v,n);
			time_b = microseconds();
			time_2 = time_b - time_a;
			time_T = (time_1-time_2) / K;
			
			printf("%10d(*)%17f%15f%15f%15f\n", n, time_T, time_T/pow(n,1.8),		//Added "(*)"
			time_T/pow(n,2), time_T/pow(n,2.2));
		}
		else
			printf("%10d%20f%15f%15f%15f\n", n, time_1, time_1/pow(n,1.8),
			time_1/pow(n,2), time_1/pow(n,2.2));
	}
}

void timesDesc_sel(){	//Selection Sort (descending init)
	double time_a, time_b, time_1, time_2, time_T;
	int n;
	printf("\nDescending initialization. Selection sort\n");
	printf("%10s%18s%15s%15s%15s\n", "Array length", "t(n)",
	"t(n)/n^1.8", "t(n)/n^2", "t(n)/n^2.2");

	for (n=500; n<=32000; n=2*n){
		int v[n];
		descending_init(v,n);
		time_a = microseconds();
		sel_sort(v,n);
		time_b = microseconds();
		time_1 = time_b - time_a;
		if (time_1 < 500){
			time_a = microseconds();
			for (int i = 1; i<=K; i++){	//K=1000
				descending_init(v,n);
				sel_sort(v,n);
			}
			time_b = microseconds();
			time_1 = time_b-time_a;
			time_a = microseconds();
			for (int i = 1; i<=K; i++)	//K=1000
				descending_init(v,n);
			time_b = microseconds();
			time_2 = time_b - time_a;
			time_T = (time_1-time_2) / K;
			
			printf("%10d(*)%17f%15f%15f%15f\n", n, time_T, time_T/pow(n,1.8),		
			time_T/pow(n,2), time_T/pow(n,2.2));
		}
		else
			printf("%10d%20f%15f%15f%15f\n", n, time_1, time_1/pow(n,1.8),
			time_1/pow(n,2), time_1/pow(n,2.2));
	}
}

void timesR_shell(){	//Selection Sort (random init)
	double time_a, time_b, time_1, time_2, time_T;
	int n;
	printf("\nRandom initialization. Shell sort\n");
	printf("%10s%18s%15s%15s%15s\n", "Array length", "t(n)",
	"t(n)/n^0.97", "t(n)/n^1.17", "t(n)/n^1.37");

	for (n=500; n<=32000; n=2*n){
		int v[n];
		random_init(v,n);
		time_a = microseconds();
		shell_sort(v,n);
		time_b = microseconds();
		time_1 = time_b - time_a;
		
		if (time_1 < 500){
			time_a = microseconds();
			for (int i = 1; i<=K; i++){	//K=1000
				random_init(v,n);
				shell_sort(v,n);
			}
			time_b = microseconds();
			time_1 = time_b-time_a;
			time_a = microseconds();
			for (int i = 1; i<=K; i++)	//K=1000
				random_init(v,n);
			time_b = microseconds();
			time_2 = time_b - time_a;
			time_T = (time_1-time_2) / K;
			
			printf("%10d(*)%17f%15f%15f%15f\n", n, time_T, time_T/pow(n,0.97),	
			time_T/pow(n,1.17), time_T/pow(n,1.37));
		}
		else
			printf("%10d%20f%15f%15f%15f\n", n, time_1, time_1/pow(n,0.97),
			time_1/pow(n,1.17), time_1/pow(n,1.37));
	}
}

void timesAsc_shell(){	//Shell Sort (ascending init)
	double time_a, time_b, time_1, time_2, time_T;
	int n;
	printf("\nAscending initialization. Shell sort\n");
	printf("%10s%18s%15s%15s%15s\n", "Array length", "t(n)",
	"t(n)/n^0.95", "t(n)/n^1.15", "t(n)/n^1.35");

	for (n=500; n<=32000; n=2*n){
		int v[n];
		ascending_init(v,n);
		time_a = microseconds();
		shell_sort(v,n);
		time_b = microseconds();
		time_1 = time_b - time_a;
		if (time_1 < 500){
			time_a = microseconds();
			for (int i = 1; i<=K; i++){	//K=1000
				ascending_init(v,n);
				shell_sort(v,n);
			}
			time_b = microseconds();
			time_1 = time_b-time_a;
			time_a = microseconds();
			for (int i = 1; i<=K; i++)	//K=1000
				ascending_init(v,n);
			time_b = microseconds();
			time_2 = time_b - time_a;
			time_T = (time_1-time_2) / K;
			
			printf("%10d(*)%17f%15f%15f%15f\n", n, time_T, time_T/pow(n,0.95),
			time_T/pow(n,1.15), time_T/pow(n,1.35));
		}
		else
			printf("%10d%20f%15f%15f%15f\n", n, time_1, time_1/pow(n,0.95),
			time_1/pow(n,1.15), time_1/pow(n,1.35));
	}
}

void timesDesc_shell(){	//Shell Sort (descending init)
	double time_a, time_b, time_1, time_2, time_T;
	int n;
	printf("\nDescending initialization. Shell sort\n");
	printf("%10s%18s%15s%15s%15s\n", "Array length", "t(n)",
	"t(n)/n^0.95", "t(n)/n^1.15", "t(n)/n^1.35");

	for (n=500; n<=32000; n=2*n){
		int v[n];
		descending_init(v,n);
		time_a = microseconds();
		shell_sort(v,n);
		time_b = microseconds();
		time_1 = time_b - time_a;
		if (time_1 < 500){
			time_a = microseconds();
			for (int i = 1; i<=K; i++){	//K=1000
				descending_init(v,n);
				shell_sort(v,n);
			}
			time_b = microseconds();
			time_1 = time_b-time_a;
			time_a = microseconds();
			for (int i = 1; i<=K; i++)	//K=1000
				descending_init(v,n);
			time_b = microseconds();
			time_2 = time_b - time_a;
			time_T = (time_1-time_2) / K;
			
			printf("%10d(*)%17f%15f%15f%15f\n", n, time_T, time_T/pow(n,0.95),		
			time_T/pow(n,1.15), time_T/pow(n,1.35));
		}
		else
			printf("%10d%20f%15f%15f%15f\n", n, time_1, time_1/pow(n,0.95),
			time_1/pow(n,1.15), time_1/pow(n,1.35));
	}
}

int main() {
    init_seed();
    printf( "**************************************************\n"
			"Check of the correct functioning of the algorithms\n"
			"**************************************************\n");
    test1();
    test2();
    test3();
    test4();
    
    printf("\n\n*************************************************************\n"
			"Computation of runtimes, empirical verification of complexity\n"
			"*************************************************************\n");
    timesR_sel();
    timesAsc_sel();
    timesDesc_sel();
    
    
    timesR_shell();
    timesAsc_shell();
    timesDesc_shell();
    
    return 0;
}
