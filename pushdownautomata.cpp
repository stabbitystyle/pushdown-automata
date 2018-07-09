// Pushdown Automata class
// Rev0 7/4/18 by William Frank

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "states.hpp"
#include "finalstates.hpp"
#include "instantaneous_description.hpp"
#include "pushdownautomata.hpp"

using namespace std;

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
    //initialID(initialState, originalInputString, initialStackCharacter);
}

void PushdownAutomata::viewDefinition() const
{

}

void PushdownAutomata::initialize(string inputString)
{

}

bool PushdownAutomata::isAccepted(InstantaneousDescription id, int numberInCurrentPath)
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