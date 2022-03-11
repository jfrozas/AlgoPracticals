/*ALGORITHMS - PRACTICAL 1: MAXIMUM SUBSEQUENCE SUM
 * 
 * By:
 * - Javier Fernández Rozas		j.frozas
 * - Pelayo Vieites Pérez		pelayo.vieites.perez
 * 
 * Date: 23 Sept 2021
 * Group: 6.1
 * 
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

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


int maxSubSum1(int v[], int n){
    int i, j;
    long thisSum, maxSum=0;
    for (i=0; i<n; i++){
        thisSum=0;
        for(j=i; j<n; j++){
            thisSum += v[j];
            if (thisSum > maxSum)
                maxSum = thisSum;
        }
    }
    return maxSum;
}


int maxSubSum2(int v[], int n){
    int j;
    long thisSum = 0;
    long maxSum = 0;
    for (j = 0; j < n; j++){
        thisSum = thisSum + v[j];
        if (thisSum > maxSum)
            maxSum = thisSum;
        else if (thisSum < 0)
            thisSum = 0;
    }
    return maxSum;
}


void print_array(int v[], int n){
    int i;
    printf("[");
    for (i=0; i<n; i++)
        printf("%3d", v[i]);
    printf(" ]");
}


void test1() {
    int n = 5, i;
    int arrs[6][5] = {
        {-9, 2, -5, -4, 6},
        {4, 0, 9, 2, 5},
        {-2,-1,-9,-7,-1},
        {9, -2, 1, -7, -8},
        {15, -2, -5, -4, 16},
        {7, -5, 6, 7, -7},
    };

    printf("\ntest 1\n");
    printf("%20s%15s%15s\n", "", "maxSubSum1", "maxSubSum2");
    for (i=0; i<6; i++){
        print_array(arrs[i],n);
        printf("%15d%15d\n", maxSubSum1(arrs[i],n), maxSubSum2(arrs[i],n));
    }

}


void test2() {
    int i, a, b;
    int v[9];
    printf("\ntest 2\n");
    printf("%33s%15s%15s\n", "", "maxSubSum1", "maxSubSum2");
    for (i=0; i<10; i++) {
        random_init(v, 9);
        print_array(v, 9);
        a = maxSubSum1(v, 9);
        b = maxSubSum2(v, 9);
        printf("%15d%15d\n", a, b);
    }
}

void test3(){	//MaxSubSum1
	double time_a, time_b, time_1, time_2, time_T;
	int n;
	printf("\ntest 3: MaxSubSum1\n");
	printf("%10s%18s%15s%15s%15s\n", "Array length", "t(n)",
	"t(n)/n^1.8", "t(n)/n^2", "t(n)/n^2.2");

	for (n=500; n<=32000; n=2*n){
		int v[n];
		random_init(v,n);
		time_a = microseconds();
		maxSubSum1(v,n);
		time_b = microseconds();
		time_1 = time_b - time_a;
		if (time_1 < 500){
			time_a = microseconds();
			for (int i = 1; i<=K; i++){	//K=1000
				random_init(v,n);
				maxSubSum1(v,n);
			}
			time_b = microseconds();
			time_1 = time_b-time_a;
			time_a = microseconds();
			for (int i = 1; i<=K; i++)	//K=1000
				random_init(v,n);
			time_b = microseconds();
			time_2 = time_b - time_a;
			time_T = (time_1-time_2) / K;
			
			printf("%10d%20f%15f%15f%15f\n", n, time_T, time_T/pow(n,1.8),
			time_T/pow(n,2), time_T/pow(n,2.2));
		}
		else
			printf("%10d%20f%15f%15f%15f\n", n, time_1, time_1/pow(n,1.8),
			time_1/pow(n,2), time_1/pow(n,2.2));
	}
}

void test4(){	//MaxSubSum4
	double time_a, time_b, time_1, time_2, time_T;
	int n;
	printf("\ntest 4: MaxSubSum2\n");
	printf("%10s%18s%15s%15s%15s\n", "Array length", "t(n)",
	"t(n)/n^0.8", "t(n)/n", "t(n)/n^1.2");

	for (n=500; n<=32000; n=2*n){
		int v[n];
		random_init(v,n);
		time_a = microseconds();
		maxSubSum2(v,n);
		time_b = microseconds();
		time_1 = time_b - time_a;
		if (time_1 < 500){
			time_a = microseconds();
			for (int i = 1; i<=K; i++){	//K=1000
				random_init(v,n);
				maxSubSum2(v,n);
			}
			time_b = microseconds();
			time_1 = time_b-time_a;
			time_a = microseconds();
			for (int i = 1; i<=K; i++)	//K=1000
				random_init(v,n);
			time_b = microseconds();
			time_2 = time_b - time_a;
			time_T = (time_1-time_2) / K;
			
			printf("%10d%20f%15f%15f%15f\n", n, time_T, time_T/pow(n,0.8),
			time_T/n, time_T/pow(n,1.2));
		}
		else
			printf("%10d%20f%15f%15f%15f\n", n, time_1, time_1/pow(n,0.8),
			time_1/n, time_1/pow(n,1.2));
	}
}

int main() {
    init_seed();
    test1();
    test2();  
    test3();
    test4();
    return 0;
}
