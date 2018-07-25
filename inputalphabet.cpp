// Input Alphabet class
// Rev0 7/4/18 by William Frank
// Rev1 7/10/18 by Cole Woodford

#include <fstream>
#include <iostream>
#include <iterator>

#include "inputalphabet.hpp"
#include "stackalphabet.hpp"
#include "uppercase.hpp"

using namespace std;

// The method load accepts a definition file and a valid Boolean as parameters.
// The definition file is checked for the input alphabet, which is then loaded into the alphabet attribute.
// If there are any characters without spaces between them, if the input alphabet keyword cannot be found,
//     if one of the input alphabet characters is from the reserved list of characters, if there are any duplicate characters,
//     or if the next keyword after the input alphabet isn’t found, valid is set to false,
//     which will then end the loading of the pushdown automata definition elsewhere in the application.
void InputAlphabet::load(ifstream& definition, string& value, bool& valid)
{
    while((definition >> value) && (uppercase(value) != "STACK_ALPHABET:"))
    {
        string uppercaseValue = uppercase(value);
        if((uppercaseValue == "INPUT_ALPHABET:") || (uppercaseValue == "STATES:") || (uppercaseValue == "TRANSITION_FUNCTION:") || (uppercaseValue == "INITIAL_STATE:") || (uppercaseValue == "START_CHARACTER:") || (uppercaseValue == "FINAL_STATES:"))
        {
            cout << "Improper keyword used in Input Alphabet: " << uppercaseValue << endl;
            valid = false;
            return;
        }
        if(value.length() == 1 && (value[0] != '\\') && (value[0] != '(') && (value[0] != ')') && (value[0] != '>') && (value[0] != ','))
        {
            bool duplicate = false;
            for(vector<char>::const_iterator it = alphabet.begin(); it != alphabet.end(); ++it)
            {
                if (*it == value[0]) {
                    cout << "Duplicate input alphabet character: " << value << endl;
                    valid = false;
                    duplicate = true;
                }
            }
            if (duplicate == false){
                alphabet.push_back(value[0]);
            }
        }
        else
        {
            cout << "Illegal input alphabet character: " << value << endl;
            valid = false;
        }
    }
    if(definition.eof())
    {
        cout << "End of file reached too soon." << endl;
        valid = false;
    }
}

// The method view prints out the input alphabet.
void InputAlphabet::view() const
{
    cout << "\u03A3 = {";
    for(vector<char>::const_iterator it = alphabet.begin(); it != alphabet.end(); ++it)
    {
        if(it == alphabet.begin())
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

// The method isElement accepts a character value as a parameter.
// If value is found within the input alphabet, true is returned.
// Otherwise, false is returned.
bool InputAlphabet::isElement(const char value) const
{
    bool isElement = false;
    for(vector<char>::const_iterator it = alphabet.begin(); it != alphabet.end(); ++it)
    {
        if(*it == value)
        {
            isElement = true;
            break;
        }
        else if(value == '\\')
        {
            isElement = true;
            break;
        }
    }
    return isElement;
}