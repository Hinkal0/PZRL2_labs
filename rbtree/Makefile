.PHONY: all clean run

TEST=rbt_test
LIBTEST=RBTreeTest

all: $(TEST)

$(TEST): BST.cpp
	g++ BST.cpp -L. -l$(LIBTEST) -o $(TEST) -std=c++11

run: all
	./$(TEST)

clean:
	rm -rf *.o $(TEST)
