

#include "prim.h"

matrix create_matrix(int n) {
	int i;
	matrix aux;
	if ((aux = malloc(n*sizeof(int *))) == NULL)
		return NULL;
	for (i=0; i<n; i++)
		if ((aux[i] = malloc(n*sizeof(int))) == NULL)
			return NULL;
	return aux;
}

void init_matrix(matrix m, int n) {
	/* Creates an undirected complete graph with random values between 1 y n */
	int i, j;
	for (i=0; i<n; i++)
		for (j=i+1; j<n; j++)
			m[i][j] = rand() % n + 1;

	for (i=0; i<n; i++)
		for (j=0; j<=i; j++)
			if (i==j)
				m[i][j] = 0;
			else
				m[i][j] = m[j][i];
}

void free_matrix(matrix m, int n) {
	int i;
	for (i=0; i<n; i++)
		free(m[i]);
	free(m);
}

void print_matrix (matrix m, int n){
	int i, j;
	for (i=0; i<n; i++){
		for (j=0; j<n; j++)
			printf("%3d  ", m[i][j]);
		printf("\n");
	}
}


void prim(matrix m, int nodes, queue *edges) {
	/* calculate the minimum spanning tree returning
	the edges of the tree in the ’edges’ queue */
	int min, i, j, k=0;
	edge a;
	
	int *closest = (int *) malloc(nodes*sizeof(int));
	int *minDistance = (int *) malloc(nodes*sizeof(int));
	create_queue(edges);
	
	minDistance[0] = -1;
	for(i = 1; i < nodes; i++) {
		closest[i] = 0;
		*(minDistance+i) = m[i][0];
	}
	
	for(int count = 0; count < nodes-1; count++) {
		min = -1; //used to represent inf
		for (j=1; j<nodes; j++)
			if (0<=minDistance[j] && (minDistance[j]<min || min==-1)){
				min = minDistance[j];
				k=j;
			}
		a = (edge){closest[k], k, m[closest[k]][k]}; //given starting vertex, ending vertex and weight
		join (edges, a);
		minDistance[k] = -1;
		for (j=1; j<nodes; j++)
			if (m[j][k] < minDistance[j]){
				minDistance[j] = m[j][k];
				closest[j] = k;
			}
	}
	
	free(closest);
	free(minDistance);
	//The information is already in *edges
}
