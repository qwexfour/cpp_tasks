CC = g++
DBGINFO = -g
CXXFLAGS = -lm -Wall -Werror -pedantic-errors --std=c++11 -O2

all: a.out

a.out: main.o mymatrix.o
	$(CC) $(CXXFLAGS) $(DBGINFO) main.o mymatrix.o -o a.out

clear:
	rm *.o a.out
