CFLAGS= -g -Wall
CC= g++
ALL= pda *.o
OBJECTS= *.o

all: pda

pda: main.cpp configurationsettings.o finalstates.o inputalphabet.o inputstrings.o instantaneousdescription.o intinput.o operations.o pushdownautomata.o stackalphabet.o states.o transition.o transitionfunction.o uppercase.o

%.o: %.c %.h
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f $(OBJECTS)

immaculate:
	rm -f $(ALL)
