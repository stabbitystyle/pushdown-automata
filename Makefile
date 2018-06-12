CC = g++
CFLAGS = -g -Wall
OBJECTS = main.o

all: pda

pda: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

.PHONY: clean
clean:
	rm -f *.o

.PHONY: immaculate
immaculate:
	rm -f pda *.o