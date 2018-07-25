CFLAGS= -g -Wall -std=c++11
CC= g++
ALL= pda *.o
OBJECTS= *.o

all: pda

pda: main.cpp inputalphabet.o stackalphabet.o states.o finalstates.o transitionfunction.o instantaneousdescription.o configurationsettings.o commandsinoperation.o commands.o pushdownautomata.o inputstrings.o intinput.o operations.o transition.o uppercase.o
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.cpp %.hpp
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f $(OBJECTS)

immaculate:
	rm -f $(ALL)
