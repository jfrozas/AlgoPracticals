#ifndef PRIM_H
#define PRIM_H

#include "queue.h"

matrix create_matrix(int n);
void init_matrix(matrix m, int n);
void free_matrix(matrix m, int n);
void print_matrix (matrix m, int n);
void prim(matrix m, int nodes, queue *edges);


#endif
