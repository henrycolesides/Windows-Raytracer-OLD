# Makefile for cpp-raytracer
CC = g++
LFLAGS = -lgdi32
PROG = raytracer
VEC = vec3
CLR = color
SHP = shapes

all: $(PROG)

$(PROG): main.o $(SHP).o $(CLR).o $(VEC).o
	$(CC) -o $@ $^ $(LFLAGS)

main.o: main.cpp $(SHP).h $(CLR).h $(VEC).h
	$(CC) -c $<

$(SHP).o: $(SHP).cpp $(SHP).h $(CLR).h $(VEC).h
	$(CC) -c $<

$(CLR).o: $(CLR).cpp $(CLR).h
	$(CC) -c $<

$(VEC).o: $(VEC).cpp $(VEC).h
	$(CC) -c $<

clean:
	rm -f *.o $(PROG) \#*