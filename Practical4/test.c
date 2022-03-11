#include "queue.h"
#include "prim.h"


matrix create_a(){
	matrix a = create_matrix(5);
	a[0][0]=a[1][1]=a[2][2]=a[3][3]=a[4][4]=0;
	a[0][1]=a[1][0]=1;
	a[0][2]=a[2][0]=8;
	a[0][3]=a[3][0]=4;
	a[0][4]=a[4][0]=7;
	a[1][2]=a[2][1]=2;
	a[1][3]=a[3][1]=6;
	a[1][4]=a[4][1]=5;
	a[2][3]=a[3][2]=9;
	a[2][4]=a[4][2]=5;
	a[3][4]=a[4][3]=3;
	return a;
}

matrix create_b(){
	
	matrix m = create_matrix(4);
	m[0][0]=m[1][1]=m[2][2]=m[3][3];
	m[0][1]=m[1][0]=1;
	m[0][2]=m[2][0]=4;
	m[0][3]=m[3][0]=7;
	
	m[1][2]=m[2][1]=2;
	m[1][3]=m[3][1]=8;
	
	m[2][3]=m[3][2]=3;
	
	return m;
}

matrix create_c(){
	
	matrix m = create_matrix(7);
	m[0][0]=m[1][1]=m[2][2]=m[3][3]=m[4][4]=m[5][5]=m[6][6]=0;
	m[0][1]=m[1][0]=7;
	m[0][2]=m[2][0]=99;
	m[0][3]=m[3][0]=5;
	m[0][4]=m[4][0]=m[0][5]=m[5][0]=m[0][6]=m[6][0]=99;
	
	m[1][2]=m[2][1]=8;
	m[1][3]=m[3][1]=9;
	m[1][4]=m[4][1]=7;
	m[1][5]=m[5][1]=m[1][6]=m[6][1]=99;
	
	m[2][3]=m[3][2]=99;
	m[2][4]=m[4][2]=5;
	m[2][5]=m[5][2]=m[2][6]=m[6][2]=99;
	
	m[3][4]=m[4][3]=15;
	m[3][5]=m[5][3]=6;
	m[3][6]=m[6][3]=99;
	
	m[4][5]=m[5][4]=8;
	m[4][6]=m[6][4]=9;
	
	m[6][5]=m[5][6]=11;
	
	return m;
}

int main(){
	
	matrix a = create_a(), b=create_b(), c=create_c();
	queue edges;
	
	printf( "*************************************************\n"
            "Check of the correct functioning of the algorithm\n"
	        "*************************************************\n");
	
	print_matrix(a,5);
	prim(a, 5, &edges);
	printf("Edges: "); show_queue(edges);
	printf("Weight: %d\n\n", getweight(edges));
	
	print_matrix(b,4);
	prim(b, 4, &edges);
	printf("Edges: "); show_queue(edges);
	printf("Weight: %d\n\n", getweight(edges));
	
	print_matrix(c,7);
	prim(c, 7, &edges);
	printf("Edges: "); show_queue(edges);
	printf("Weight: %d\n\n", getweight(edges));
	
}
