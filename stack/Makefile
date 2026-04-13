.PHONY: all clean run

TEST=stack_test
SOURCE=Stack.cpp
LIBTEST=StackTest

all: $(TEST)

$(TEST): $(SOURCE)
	g++ $< -o $@ -L. -l$(LIBTEST) -std=c++11

clean:
	rm -rf *.o $(TEST)

run: all
	./$(TEST)
