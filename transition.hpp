#ifndef TRANSITION_HPP
#define TRANSITION_HPP

#include <string>

using namespace std;

// The class Transition is a class which stores the information about a single transition for the pushdown automata.
class Transition
{
	private:
		string source;
		char read;
		string destination;
		char stack;
		string push;
	public: 
        Transition(string sourceState, char readCharacter, string destinationState, char stackCharacter, string pushString);
        string sourceState() const;
        char readCharacter() const;
        string destinationState() const;
		char stackCharacter() const;
        string pushString() const;
};

#endif