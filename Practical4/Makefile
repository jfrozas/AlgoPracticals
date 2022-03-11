all: p4 test clean

p4: prac4alg.o queue.o prim.o
	gcc prac4alg.o queue.o prim.o -lm -o p4

test: test.o queue.o prim.o
	gcc test.o queue.o prim.o -o test

prim.o: prim.c prim.h queue.h
	gcc -c -g -Wall prim.c

test.o: test.c queue.h prim.h
	gcc -c -g -Wall test.c

prac4alg.o: prac4alg.c queue.h prim.h
	gcc -c -g -Wall prac4alg.c -lm

queue.o: queue.c queue.h
	gcc -c -g -Wall queue.c

clean:
	rm *.o
