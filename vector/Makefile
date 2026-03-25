.PHONY: all clean run

all: vector_test

vector_test: Vector.cpp 
	g++ $> -o $@ -L. -lVectorTest -std=c++11

clean:
	rm -rf *.o vector_test

run: all
	./vector_test
