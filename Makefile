CXX ?= g++ #CXX will always be set!
CXXFLAGS ?= -O3 -ffast-math -funroll-loops

CXXFLAGS+=-Wall
TEST_CXXFLAGS+=-std=c++14

all:	test

catch.o : catch.cpp
	$(CXX) $(TEST_CXXFLAGS) $(CXXFLAGS) -c -o $@ $^

test_clear_method: test_clear_method.o Cover_Tree_Point.o catch.o
	$(CXX) $(TEST_CXXFLAGS) $(CXXFLAGS) -o $@ $^

test_tree: test_tree.o Cover_Tree_Point.o catch.o
	$(CXX) $(TEST_CXXFLAGS) $(CXXFLAGS) -o $@ $^

clean:
	rm *.o test_*

.PRECIOUS: catch.o
