#include "queue.h"

void create_queue (queue *Q) {
	Q->size = 0;
	Q->front_index = 0;
	Q->rear_index = -1;
}

int isEmptyQueue (queue Q) {
	return (Q.size == 0) ;
}

void Increment (int * x) {  
	if (++(*x) == MAX_SIZE)
		*x = 0;
}

void enqueue ( element_type x , queue *Q) {
	if (Q->size == MAX_SIZE) {
		printf ("error: full queue: %d\n", Q->size);
		exit (EXIT_FAILURE) ;
	}
	Q->size++;
	Increment (&(Q->rear_index)) ;
	
	Q->vector [Q->rear_index ] = x ;
}

element_type front (queue Q) {
	if (isEmptyQueue (Q)) {
		printf("Error: Empty queue\n");
		exit (EXIT_FAILURE) ;
	}
	return (Q.vector [Q.front_index]);
}


element_type dequeue (queue *Q) {
	element_type x ;
	if (isEmptyQueue(*Q)){
		printf("Error: Empty queue\n");
		exit (EXIT_FAILURE);
	}
		
	Q->size--;
	x = Q->vector[Q->front_index];
	Increment (&(Q->front_index)) ;
	return x;
}

void print_edge(element_type eToPrint){
	printf("(%d, %d)   ", eToPrint.x, eToPrint.y);
	
}

void show_queue(queue Q){
	int i, j;
	j = Q.front_index;
	for (i=0; i<Q.size; i++){
		print_edge(Q.vector[j]);
		Increment(&j);
	}
	printf("\n");
}

int getweight(queue Q){
	int i, j, w=0;
	j = Q.front_index;
	for (i=0; i<Q.size; i++){
		w+=Q.vector[j].weight;
		Increment(&j);
	}
	return w;
}

void join(queue *Q, element_type toAdd){
	int i, j=Q->front_index;
	if (Q->size == MAX_SIZE){
		printf("Error: there is not enough space for the edge.\n");
		return;
	}
	for (i=0; i<(Q->size); i++){
		edge a = Q->vector[j];
		if ((a.x == toAdd.x && a.y == toAdd.y) || (a.x == toAdd.y && a.y == toAdd.x))
			return;
		Increment(&j);
	}
	//At this point, the element was not found and there is space for it
	//j has the position where it has to be inserted
	enqueue(toAdd, Q);
	
}





