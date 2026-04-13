.PHONY: all clean run

TEST=stack_test
SOURCE=Stack.cpp
LIBTEST=StackTest

all: $(TEST)

$(TEST): Vector.o LinkedList.o StackImplementation.o Stack.o
	g++ Stack.o Vector.o LinkedList.o StackImplementation.o -o $@ -L. -l$(LIBTEST) -std=c++11

Stack.o: Stack.cpp
	g++ -c Stack.cpp

Vector.o: Vector.cpp
	g++ -c Vector.cpp

LinkedList.o: LinkedList.cpp
	g++ -c LinkedList.cpp

StackImplementation.o: StackImplementation.cpp
	g++ -c StackImplementation.cpp

clean:
	rm -rf *.o $(TEST)

run: all
	./$(TEST)
