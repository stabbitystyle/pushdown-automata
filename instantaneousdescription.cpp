// Instantaneous Description class
// Rev0 7/8/18 by William Frank

#include <string>
#include <iostream>

#include "instantaneousdescription.hpp"
#include "configurationsettings.hpp"

// What is this?
//#include "operations.hpp"

using namespace std;

InstantaneousDescription::InstantaneousDescription(string initialState, string inputString, char startCharacter) : 
    currentState(""), remainingInputString(""), stack("")
{
}

void InstantaneousDescription::view(ConfigurationSettingsPointer configurationSettingsPointer) const
{
    int maximumNumberOfCharacters = configurationSettingsPointer->maximumNumberOfCharacters();
    cout << "(" << currentState << ")" << truncated(visible(remainingInputString), maximumNumberOfCharacters) << ","
        << truncated(visible(stack), maximumNumberOfCharacters) << ")";
}

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

string InstantaneousDescription::state() const
{
    return currentState;
}

char InstantaneousDescription::inputCharacter() const
{
    return remainingInputString.at(0);
}

char InstantaneousDescription::topOfStack() const
{
    return stack.at(0);
}

bool InstantaneousDescription::isEmptyRemainingInputString() const
{
    return remainingInputString.empty();
}

bool InstantaneousDescription::isEmptyStack() const
{
    return stack.empty();
}