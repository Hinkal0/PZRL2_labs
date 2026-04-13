.PHONY: all clean run

TEST=stack_test
SOURCE=Stack.cpp
LIBTEST=StackTest

all: $(TEST)

$(TEST): Stack.o VectorStack.o LinkedListStack.o
	g++ Stack.o VectorStack.o LinkedListStack.o -o $@ -L. -l$(LIBTEST) -std=c++11

Stack.o: Stack.cpp
	g++ -c Stack.cpp

VectorStack.o: VectorStack.cpp
	g++ -c Vector.cpp

LinkedListStack.o: LinkedListStack.cpp
	g++ -c LinkedListStack.cpp

clean:
	rm -rf *.o $(TEST)

run: all
	./$(TEST)
