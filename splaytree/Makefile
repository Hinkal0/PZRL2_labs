.PHONY: all clean run

TEST=splay_test

all: $(TEST)

$(TEST): main.cpp
	g++ main.cpp -o $(TEST) -std=c++11

run: all
	./$(TEST)

clean:
	rm -rf *.o $(TEST)
