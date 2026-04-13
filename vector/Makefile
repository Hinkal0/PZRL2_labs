.PHONY: all clean run

TEST=vector_test
SOURCE=Vector.cpp
LIBTEST=VectorTest

all: $(TEST)

$(TEST): $(SOURCE)
	g++ $< -o $@ -L. -l$(LIBTEST) -std=c++11

clean:
	rm -rf *.o $(TEST)

run: all
	./$(TEST)
