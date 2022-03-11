

#include "queue.h"
#include "prim.h"

#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

#define K 1000
#define BOUND_STRING_SIZE 15


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


void calculateTimes(float underestimated, float tight, float overestimated) 
{
	int n;
	double time_a, time_b, time_1, time_2, time_T;

	char underString[BOUND_STRING_SIZE], tightString[BOUND_STRING_SIZE], 
		overString[BOUND_STRING_SIZE];
		
	sprintf(underString, "t(n)/n^%1.2f", underestimated);
	sprintf(tightString, "t(n)/n^%1.2f", tight);
	sprintf(overString, "t(n)/n^%1.2f", overestimated);
	printf("%15s%17s%15s%15s%15s\n", "Number of nodes", "t(n)",
	underString, tightString, overString);
	
	for (n=25; n<=800; n=2*n){
		matrix m = create_matrix(n);
		queue edges;
		init_matrix(m, n);
		
		time_a = microseconds();
		prim (m, n, &edges);
		time_b = microseconds();
		
		time_1 = time_b - time_a;
		free_matrix(m,n);
		
		
		if (time_1 < 500){
			m=create_matrix(n);

			time_a = microseconds();
			for (int i = 1; i<=K; i++){	//K=1000
				init_matrix(m, n);
				prim(m, n, &edges);
			}
			time_b = microseconds();
			time_1 = time_b-time_a;
			
			time_a = microseconds();
			
			for (int i = 1; i<=K; i++){	//K=1000
				init_matrix(m, n);
			}
			
			time_b = microseconds();
			time_2 = time_b - time_a;
			time_T = (time_1-time_2) / K;
			free_matrix(m, n);
			
			printf("%12d(*)%17f%15f%15f%15f\n", n, time_T, time_T/pow(n,underestimated),
			time_T/pow(n,tight), time_T/pow(n,overestimated));
		}
		else
			printf("%12d%20f%15f%15f%15f\n", n, time_1, time_1/pow(n,underestimated),
			time_1/pow(n,tight), time_1/pow(n,overestimated));
	}
	printf("\n\n");
}



int main(){
	printf("\n\n"
           "*************************************************************\n"
	       "Computation of runtimes, empirical verification of complexity\n"
	       "*************************************************************\n");
	calculateTimes(2.0, 2.1, 2.2);
	
	return 0;
}
