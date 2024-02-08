# Makefile for cpp-raytracer
CC = g++
LFLAGS = -lgdi32
PROG = raytracer

all: $(PROG)

$(PROG): main.o
	$(CC) -o $@ $< $(LFLAGS)

main.o: main.cpp
	$(CC) -c $<

clean:
	rm -f *.o $(PROG) \#*