# Makefile for assignment no. #2
PROG = ex2_q1

all: $(PROG) test

test: ex2_q1
	./ex2_q1 11 24 36 7 5  > out.log
	
ex2_q1.o: $(PROG).c factors
	gcc -Wall -c $(PROG).c

factors.o: factors.c
	gcc -Wall -c factors.c

clean: 
	rm -v *.o *.log *.txt $(PROG) factors
