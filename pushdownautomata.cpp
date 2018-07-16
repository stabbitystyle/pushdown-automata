// Pushdown Automata class
// Rev0 7/4/18 by William Frank

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "states.hpp"
#include "finalstates.hpp"
#include "instantaneousdescription.hpp"
#include "pushdownautomata.hpp"
#include "stackalphabet.hpp"
#include "transitionfunction.hpp"
#include "inputalphabet.hpp"
#include "configurationsettings.hpp"

using namespace std;

ConfigurationSettingsPointer PushdownAutomata::configurationSettingsPointer = 0;

PushdownAutomata::PushdownAutomata(string definitionFileName)
{
    ifstream definition(definitionFileName.c_str(), ifstream::in);
    string value;

    cout << endl;
    if(definition.fail())
    {
        cout << "Error: failed to open file " << definitionFileName << endl;
        valid = false;
    }
}

bool PushdownAutomata::isAccepted(InstantaneousDescription id, int numberInCurrentPath)
{
    bool performedTransition = false;
    int index = 0;
    int count = 0;
    string destinationState;
    string pushString;
    InstantaneousDescription nextID;

    cout << numberOfTransitions << ". [" << numberInCurrentPath << "] ";
    id.view(configurationSettingsPointer);
    cout << endl;

    if(finalStates.isElement(id.state()) && id.isEmptyRemainingInputString())
    {
        return true;
    }
    if(!id.isEmptyRemainingInputString() && !id.isEmptyStack())
    {
        count = transitionFunction.transitionCount(id.state(), id.inputCharacter(), id.topOfStack());
        for(index = 0; index < count; ++index)
        {
            transitionFunction.getTransition(index, id.state(), id.inputCharacter(), id.topOfStack(), destinationState, pushString);
            id.performTransition(destinationState, pushString, nextID);
            performedTransition = true;
            ++numberOfTransitions;
            if(isAccepted(nextID, numberInCurrentPath + 1))
            {
                return true;
            }
        }
    }

    if(!id.isEmptyStack())
    {
        count = transitionFunction.lambdaTransitionCount(id.state(), id.topOfStack());
        for(index = 0; index < count; ++index)
        {
            transitionFunction.getLambdaTransition(index, id.state(), id.topOfStack(), destinationState, pushString);
            id.performLambdaTransition(destinationState, pushString, nextID);
            performedTransition = true;
            ++numberOfTransitions;
            if(isAccepted(nextID, numberInCurrentPath + 1))
            {
                return true;
            }
        }
    }
    if(!performedTransition)
    {
        cout << "Crash " << ++numberOfCrashes << " occured." << endl;
    }
    
    return false;
}

// points the configurationSettingsPointer at a configurationSettings object referenced by configurationSettings
void PushdownAutomata::link(ConfigurationSettings& configurationSettings)
{
    configurationSettingsPointer = &configurationSettings;
}

// The method viewDefinition prints out the description of the Pushdown Automaton as found in the definition file,
//		followed by the definition of the Pushdown Automaton.
// The definition for the Pushdown Automaton is printed using methods for the various classes which print their respective information,
//		after which the entire definition will have been printed.
void PushdownAutomata::viewDefinition() const
{
	for (vector<string>::const_iterator it = description.begin(); it != description.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl << endl;

	states.view();
	cout << endl;

	inputAlphabet.view();
	cout << endl;

	stackAlphabet.view();
	cout << endl;

	transitionFunction.view();
	cout << endl;

	cout << "q0 = " << initialState;
	cout << endl << endl;

	finalStates.view();
	cout << endl;
}

// The method initialize will accept inputString, which is the string to be tested on the Pushdown Automaton.
// It will store inputString in originalInputString, and then set the operating Boolean to true.
// It will also set numberOfTransitions, numberOfCrashes, and numberOfTransitionsInSuccessfulPath to 0, and the used Boolean to true.
void PushdownAutomata::initialize(string inputString)
{
	originalInputString = inputString;
	currentState = initialState;
	numberOfTransitions = 0;
	numberOfCrashes = 0;
	numberOfTransitionsInSuccessfulPath = 0;
	used = true;
	operating = true;
	accepted = false;
	rejected = false;
}

// The method terminateOperation terminates operation of the Pushdown Automaton.
// It sets operating attribute to false.
void PushdownAutomata::terminateOperation()
{
	operating = false;
}

// The method inputString returns the attribute originalInputString.
string PushdownAutomata::inputString() const
{
	return originalInputString;
}

// The method totalNumberOfTransitions returns the numberOfTransitions attribute.
int PushdownAutomata::totalNumberOfTransitions() const
{
    return numberOfTransitions;
}

// The method totalNumberOfCrashes returns the numberOfCrashes attribute.
int PushdownAutomata::totalNumberOfCrashes() const
{
	return numberOfCrashes;
}

// The method isValidDefinition returns the attribute valid.
bool PushdownAutomata::isValidDefinition() const
{
    return valid;
}

// The method isValidInputString accepts a String named value as a parameter, which it then checks against the Pushdown Automaton definition to determine whether it�s a valid string.
// It returns a Boolean value depending on the result.
bool PushdownAutomata::isValidInputString(string value) const
{
	bool isValid = true;
	for (string::const_iterator it = value.begin(); it != value.end(); ++it)
	{
		if (!inputAlphabet.isElement(*it))
		{
			isValid = false;
		}
	}
	return isValid;
}

// The method isUsed returns the attributed used.
bool PushdownAutomata::isUsed() const
{
    return used;
}

// The method isOperating returns the attribute operating.
bool PushdownAutomata::isOperating() const
{
    return operating;
}

// The method isAcceptedInputString returns the attribute accepted.
bool PushdownAutomata::isAcceptedInputString() const
{
    return accepted;
}

// The method isRejectedInputString returns the attribute rejected.
bool PushdownAutomata::isRejectedInputString() const
{
    return rejected;
}