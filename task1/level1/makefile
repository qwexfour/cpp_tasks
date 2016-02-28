CC = g++
DBGINFO = -g
CFLAGS = -lm -g -Wall -Werror -pedantic-errors --std=c++98 -O2

all: a.out

a.out: main.o bitarraylib.o sievelib.o
	$(CC) $(CFLAGS) $(DBGINFO) main.o bitarraylib.o sievelib.o -o a.out

main.o: main.cpp bitarraylib.h sievelib.h
	$(CC) $(CFLAGS) $(DBGINFO) -c main.cpp -o main.o

sievelib.o: sievelib.cpp  sievelib.h
	$(CC) $(CFLAGS) $(DBGINFO) -c sievelib.cpp -o sievelib.o

bitarraylib.o: bitarraylib.cpp bitarraylib.h
	$(CC) $(CFLAGS) $(DBGINFO) -c bitarraylib.cpp -o bitarraylib.o

clear:
	rm *.o a.out
