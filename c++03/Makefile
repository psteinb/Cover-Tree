CXX ?= g++ #CXX will always be set!
CXXFLAGS ?= -O3 -ffast-math -funroll-loops

CXXFLAGS+=-Wall

all:	test

Cover_Tree_Point.o: Cover_Tree_Point.h Cover_Tree_Point.cc
	$(CXX) -c $(CXXFLAGS) Cover_Tree_Point.cc

test: test.cc Cover_Tree.h Cover_Tree_Point.o Cover_Tree_Point.h Cover_Tree_Point.cc
	$(CXX) test.cc $(CXXFLAGS) -o test  Cover_Tree_Point.o

clean:
	rm *.o test

.PRECIOUS: catch.o
