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
//#include "configurationsettings.hpp"

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
            id.performLamdaTransition(destinationState, pushString, nextID);
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

void PushdownAutomata::link(ConfigurationSettings& configurationSettings)
{
    configurationSettingsPointer = &configurationSettings;
}

void PushdownAutomata::viewDefinition() const
{

}

void PushdownAutomata::initialize(string inputString)
{

}

void PushdownAutomata::terminateOperation()
{

}

string PushdownAutomata::inputString() const
{

}

int PushdownAutomata::totalNumberOfTransitions() const
{
    return numberOfTransitions;
}

bool PushdownAutomata::isValidDefinition() const
{
    return valid;
}

bool PushdownAutomata::isValidInputString(string value) const
{

}

bool PushdownAutomata::isUsed() const
{
    return used;
}

bool PushdownAutomata::isOperating() const
{
    return operating;
}

bool PushdownAutomata::isAcceptedInputString() const
{
    return accepted;
}

bool PushdownAutomata::isRejectedInputString() const
{
    return rejected;
}