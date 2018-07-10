// Instantaneous Description class
// Rev0 7/8/18 by William Frank

#include <string>

#include "instantaneousdescription.hpp"

using namespace std;

InstantaneousDescription::InstantaneousDescription(string initialState, string inputString, char startCharacter) : 
    currentState(""), remainingInputString(""), stack("")
{
}

void InstantaneousDescription::view()
{
}

void InstantaneousDescription::performTransition(string destinationState, string pushString, InstantaneousDescription nextID)
{

}

void InstantaneousDescription::performLambdaTransition(string destinationState, string pushString, InstantaneousDescription nextID)
{

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