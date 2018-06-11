CC = g++
CFLAGS = -g -Wall
OBJECTS = pda.o

all: pda

pda: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

pda.o: main.cpp
	$(CC) $(CFLAGS) -c tm.cpp

.PHONY: clean
clean:
	rm -f *.o

.PHONY: immaculate
immaculate:
	rm -f pda *.o