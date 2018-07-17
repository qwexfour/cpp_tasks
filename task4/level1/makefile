CXX = g++
DBGINFO = -g
CXXFLAGS = -lm -Wall -Werror -pedantic-errors --std=c++11 -O0

all: a.out

a.out: main.o mymatrix.o
	$(CXX) $(CXXFLAGS) $(DBGINFO) main.o mymatrix.o -o a.out

main.o: main.cpp mymatrix.hpp
	$(CXX) $(CXXFLAGS) $(DBGINFO) -c main.cpp -o main.o

mymatrix.o: mymatrix.cpp mymatrix.hpp
	$(CXX) $(CXXFLAGS) $(DBGINFO) -c mymatrix.cpp -o mymatrix.o

.PHONY: clean

clean:
	rm *.o a.out
