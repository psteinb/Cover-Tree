CXX ?= g++ #CXX will always be set!
CXXFLAGS ?= -O3 -ffast-math -funroll-loops

CXXFLAGS+=-std=c++14 -Wall

TEST_SRCS = $(wildcard test_*.cpp)
TEST_APPS = $(TEST_SRCS:%.cpp=%)

all: tests

catch.o : catch.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

test_clear_method: test_clear_method.o Cover_Tree_Point.o catch.o
	$(CXX) $(CXXFLAGS) -o $@ $^

test_tree: test_tree.o Cover_Tree_Point.o catch.o
	$(CXX) $(CXXFLAGS) -o $@ $^

bench_tree: bench_tree.o Cover_Tree_Point.o catch.o
	$(CXX) $(CXXFLAGS) -o $@ $^

tests: $(TEST_APPS)

test_run: $(TEST_APPS)
	@$(foreach item,$(TEST_APPS),echo $(item);./$(item);)

benchmark_run:
	@./bench_tree

clean:
	rm *.o test_*

.PRECIOUS: catch.o
