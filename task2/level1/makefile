CC = g++
DBGINFO = -g
CXXFLAGS = -lm -g -Wall -Werror -pedantic-errors --std=c++11 -O2

all: a.out

a.out: main.o listlib.o
	$(CC) $(CXXFLAGS) $(DBGINFO) main.o listlib.o -o a.out

clear:
	rm *.o a.out
