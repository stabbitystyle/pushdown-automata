CFLAGS= -g -Wall -std=c++11
CC= g++
ALL= pda *.o
OBJECTS= *.o

all: pda

pda: main.cpp pushdownautomata.o commands.o commandsinoperation.o configurationsettings.o finalstates.o inputalphabet.o inputstrings.o instantaneousdescription.o intinput.o operations.o stackalphabet.o states.o transition.o transitionfunction.o uppercase.o
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.cpp %.hpp
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f $(OBJECTS)

immaculate:
	rm -f $(ALL)
