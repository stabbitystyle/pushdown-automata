// Instantaneous Description class
// Rev0 7/8/18 by William Frank

#ifndef INSTANTANEOUSDESCRIPTION_HPP
#define INSTANTANEOUSDESCRIPTION_HPP

#include <string>

#include "configurationsettings.hpp"

using namespace std;

// The Instantaneous description of a pushdown automaton provides the current configuration of the pushdown automaton during operation on an input string.
// It consists of the current state, the remaining input string, and the stack.
// The initial ID is the start state, the entire input string and the initial stack character.
// The Instantaneous Description will perform a transition based on the data it stores to make a new Instantaneous Description with the changes from the transitions.      
class InstantaneousDescription
{
	private:
		string currentState;
		string remainingInputString;
		string stack;
	public:
		InstantaneousDescription();
		InstantaneousDescription(string initialState, string inputString, char startCharacter);
		string view(ConfigurationSettingsPointer configurationSettingsPointer) const;
		void performTransition(string destinationState, string pushString, InstantaneousDescription& nextID);
		void performLambdaTransition(string destinationState, string pushString, InstantaneousDescription& nextID);
		string state() const;
		char inputCharacter() const;
		char topOfStack() const;
		bool isEmptyRemainingInputString() const;
		bool isEmptyStack() const;
};
typedef InstantaneousDescription* InstantaneousDescriptionPointer;

#endif