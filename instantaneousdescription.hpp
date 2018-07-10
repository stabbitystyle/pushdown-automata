// Instantaneous Description class
// Rev0 7/8/18 by William Frank

#ifndef INSTANTANEOUSDESCRIPTION_HPP
#define INSTANTANEOUSDESCRIPTION_HPP

#include <string>

//#include "configurationsettings.hpp"

using namespace std;

class InstantaneousDescription
{
	private:
		string currentState;
		string remainingInputString;
		string stack;
	public:
		InstantaneousDescription(string initialState, string inputString, char startCharacter);
		void view();
		void performTransition(string destinationState, string pushString, InstantaneousDescription nextID);
		void performLambdaTransition(string destinationState, string pushString, InstantaneousDescription nextID);
		string state() const;
		char inputCharacter() const;
		char topOfStack() const;
		bool isEmptyRemainingInputString() const;
		bool isEmptyStack() const;
};

#endif