// Instantaneous Description class
// Rev0 7/8/18 by William Frank

#ifndef INSTANTANEOUS_DESCRIPTION_HPP
#define INSTANTANEOUS_DESCRIPTION_HPP

#include <string>

using namespace std;

class InstantaneousDescription
{
	private:
		string currentState;
		string remainingInputString;
		string stack;
	public:
		InstantaneousDescription(string initialState, string inputString, char startCharacter);
		void performTransition(string destinationState, string pushString, InstantaneousDescription nextID);
		void performLambdaTransition(string destinationState, string pushString, InstantaneousDescription nextID);
		string state() const;
		char inputCharacter() const;
		char topOfStack() const;
		bool isEmptyRemainingInputString() const;
		bool isEmptyStack() const;
};

#endif