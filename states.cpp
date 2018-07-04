// States class
// Rev0 7/4/18 by William Frank

#include <fstream>
#include <iostream>
#include <string>
#include <iterator>

#include "states.hpp"
#include "uppercase.hpp"

using namespace std;

// The method load accepts a definition file and a valid Boolean as parameters.
// The definition file is checked for states, which are then loaded into the names StringVector attribute.
// If the states function keyword cannot be found, if there is a duplicate state,
//     if one of the reserved characters is used within any of the state names, or if the next keyword after the states isn’t found,
//     valid is set to false, which will then end the loading of the pushdown automata definition elsewhere in the application.
void States::load(ifstream& definition, bool& valid)
{
    string value;
    while((definition >> value) && (uppercase(value) != "INPUT_ALPHABET:"))
    {
        string uppercaseValue = uppercase(value);
        if((uppercaseValue == "STATES:") || (uppercaseValue == "TAPE_ALPHABET:") || (uppercaseValue == "TRANSITION_FUNCTION:") || (uppercaseValue == "INITIAL_STATE:") || (uppercaseValue == "BLANK_CHARACTER:") || (uppercaseValue == "FINAL_STATES:"))
        {
            cout << "Improper keyword used in States: " << uppercaseValue << endl;
            valid = false;
            return;
        }
        for(string::iterator it = value.begin(); it != value.end(); ++it)
        {
            if((!isalnum(*it)) && (*it != '_'))
            {
                cout << "Illegal character used in state " << value << endl;
                valid = false;
            }
        }
        names.push_back(value);
    }
    if(definition.eof())
    {
        cout << "End of file reached too soon." << endl;
        valid = false;
    }
}

// The method view prints out a list of all of the states in the pushdown automata stored in the attribute names.
void States::view() const
{
    cout << "Q = {";
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
bool States::isElement(const string value) const
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