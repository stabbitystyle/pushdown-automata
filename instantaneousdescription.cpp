// Instantaneous Description class
// Rev0 7/8/18 by William Frank

#include <string>
#include <iostream>

#include "instantaneousdescription.hpp"
#include "configurationsettings.hpp"
#include "operations.hpp"

using namespace std;

InstantaneousDescription::InstantaneousDescription() :
	currentState(""), remainingInputString(""), stack("")
{
}

// The method InstantaneousDescription constructs the initial instantaneous description for the operation of the pushdown automaton from the initial state,
//		the input string, and the start character on the stack. 
InstantaneousDescription::InstantaneousDescription(string initialState, string inputString, char startCharacter) : 
    currentState(""), remainingInputString(""), stack("")
{
}

// The method view displays the formatted instantaneous description of the pushdown automaton on the console,
//		truncating the remaining input string with the reserved character '>' if the length exceeds the maximum number of characters to display.
// Truncation of the stack is performed the same way. 
void InstantaneousDescription::view(ConfigurationSettingsPointer configurationSettingsPointer) const
{
    int maximumNumberOfCharacters = configurationSettingsPointer->getMaximumNumberOfCells();
    cout << "(" << currentState << ")" << truncated(visible(remainingInputString), maximumNumberOfCharacters) << ","
        << truncated(visible(stack), maximumNumberOfCharacters) << ")";
}

// The method performTransition performs the specified transition on the instantaneous description,
//		generating the next instantaneous description of the pushdown automaton.
// The input character is read in performing this transition.
void InstantaneousDescription::performTransition(string destinationState, string pushString, InstantaneousDescription& nextID) const
{
    nextID.currentState = destinationState;
    nextID.remainingInputString = remainingInputString;
    nextID.stack = pushString + stack.substr(1, stack.length() - 1);
}

void InstantaneousDescription::performLambdaTransition(string destinationState, string pushString, InstantaneousDescription& nextID) const
{
    nextID.currentState = destinationState;
    nextID.remainingInputString = remainingInputString.substr(1, remainingInputString.length() - 1);
    nextID.stack = pushString + stack.substr(1, stack.length() - 1);
}

// The method state reteurns the currentState.
string InstantaneousDescription::state() const
{
    return currentState;
}

// The method inputCharacter returns the first character of the remaining input string.
char InstantaneousDescription::inputCharacter() const
{
    //if(remainingInputString.empty())
    //{
    //    // still shakey about this, probably need advice on how to handle exceptions
    //    throw emptyRemainingInputString("Remaining input string is empty");
    //}
    return remainingInputString.at(0);
}

// The method topOfStack returns the character on the top of the stack.
char InstantaneousDescription::topOfStack() const
{
    //if(stack.empty())
    //{
    //    // still shakey about this, probably need advice on how to handle exceptions
    //    throw emptyStack("Stack is empty");
    //}
    return stack.at(0);
}

// The method isEmptyRemainingInputString returns a value of true if the remaining input string is empty.
// Otherwise, it returns a value of false.
bool InstantaneousDescription::isEmptyRemainingInputString() const
{
    return remainingInputString.empty();
}

// The method isEmptyStack returns a value of true if the remaining input string is empty.
// Otherwise, it returns a value of false.
bool InstantaneousDescription::isEmptyStack() const
{
    return stack.empty();
}