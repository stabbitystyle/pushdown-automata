#include <string>

#include "transition.hpp"

using namespace std;

// The method Transition is the constructor for the Transition class.
// It accepts a sourceState, a readCharacter, a destinationState, a writeCharacter, and a moveDirection as parameters.
// The constructor then sets all of the local attributes equal to those parameters.
Transition::Transition(string sourceState, char readCharacter, string destinationState, char stackCharacter, string pushString) :
	source(sourceState), read(readCharacter), destination(destinationState), stack(stackCharacter), push(pushString)
{
}

// The method sourceState returns the source attribute.
string Transition::sourceState() const
{
	return source;
}

// The method readCharacter returns the read attribute.
char Transition::readCharacter() const
{
	return read;
}

// The method destinationState returns the destination attribute.
string Transition::destinationState() const
{
	return destination;
}

// The method stackCharacter returns the write attribute.
char Transition::stackCharacter() const
{
	return stack;
}

// The method moveDirection returns the move attribute.
string Transition::pushString() const
{
	return push;
}