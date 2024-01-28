CC = g++
CFLAGS = -g -Wall
LFLAGS = -lSDL2
EXE = main3

all: $(EXE).cpp
	$(CC) $(EXE).cpp $(CFLAGS) $(LFLAGS) -o $(EXE)

clean:
	rm -f *.o $(EXE) \#*
