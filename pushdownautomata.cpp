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

ConfigurationSettingsPointer PushdownAutomata::configurationsettingsPointer = 0;

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

}

void PushdownAutomata::link(Configurationsettings& configurationSettings)
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