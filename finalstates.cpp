// Final States class
// Rev0 7/4/18 by William Frank
// Rev1 7/10/18 by Cole Woodford

#include <string>
#include <fstream>
#include <iostream>
#include <iterator>
#include <cctype>

#include "finalstates.hpp"
#include "uppercase.hpp"

using namespace std;

// The method load accepts a definition file and a valid Boolean as parameters.
// The definition file is checked for states, which are then loaded into the names StringVector attribute.
// If the states function keyword cannot be found, if there is a duplicate state,
//     or if one of the reserved characters is used within any of the state names, valid is set to false,
//     which will then end the loading of the pushdown automata definition elsewhere in the application.
void FinalStates::load(ifstream& definition, string& value, bool& valid)
{
    while((definition >> value))
    {
        string uppercaseValue = uppercase(value);
        if((uppercaseValue == "STATES:") || (uppercaseValue == "INPUT_ALPHABET:") || (uppercaseValue == "STACK_ALPHABET:") || (uppercaseValue == "TRANSITION_FUNCTION:") || (uppercaseValue == "INITIAL_STATE:") || (uppercaseValue == "BLANK_CHARACTER:") || (uppercaseValue == "FINAL_STATES:"))
        {
            cout << "Improper keyword used in Final States: " << uppercaseValue << "." << endl;
            valid = false;
            return;
        }
        for(string::iterator it = value.begin(); it != value.end(); ++it)
        {
            if((!isalnum(*it)) && (*it != '_'))
            {
                cout << "Illegal character used in final state " << value << "." << endl;
                valid = false;
            }
        }
        bool duplicate = false;
        for(vector<string>::const_iterator it = names.begin(); it != names.end(); ++it)
        {
            if (*it == value) {
                cout << "Duplicate final state: " << value << endl;
                valid = false;
                duplicate = true;
            }
        }
        if (duplicate == false){
            names.push_back(value);
        }
    }
}

// The method validate accepts a valid Boolean as a parameter.
// The method validate will check to see that all of the states in the names attributes are found within the States class’ attribute names.
// This is required because the set of states in FinalStates is a subset of the set of states in States.  
void FinalStates::validate(const States& states, bool& valid) const
{
    for(vector<string>::const_iterator it = names.begin(); it != names.end(); ++ it)
    {
        if(!states.isElement(*it))
        {
            cout << "Final state " << *it << " is not in states" << endl;
            valid = false;
        }
    }
}

// The method view prints out a list of all of the final states in the pushdown automaton stored in the attribute names.
void FinalStates::view() const
{
    cout << "F = {";
    for(vector<string>::const_iterator it = names.begin(); it != names.end(); ++it)
    {
        if(it == names.begin())
        {
            cout << *it;
        }
        else
        {
            cout << ", " << *it;
        }
    }
    cout << "}" << std::endl;
}

// The method isElement accepts a parameter value, which is a string.
// It then checks the elements of the attribute names until either a match is found or the end of the vector is reached.
// If a match is found, true is returned, otherwise, false is returned.
bool FinalStates::isElement(const string value) const
{
    bool isElement = false;
    for(vector<string>::const_iterator it = names.begin(); it != names.end(); ++it)
    {
        if(*it == value)
        {
            isElement = true;
            break;
        }
    }
    return isElement;
}
