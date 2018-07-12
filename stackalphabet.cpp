// Stack Alphabet class
// Rev0 7/4/18 by William Frank
// Rev1 7/10/18 by Cole Woodford

#include <fstream>
#include <iostream>
#include <iterator>

#include "stackalphabet.hpp"
#include "uppercase.hpp"

using namespace std;

// The method load accepts a definition file and a valid Boolean as parameters.
// The definition file is checked for the stack alphabet, which is then loaded into the alphabet attribute.
// If there are any characters without spaces between them, if the stack alphabet keyword cannot be found,
//     if one of the stack alphabet characters is from the reserved list of characters, if there are any duplicate characters,
//     or if the next keyword after the input alphabet isn’t found, valid is set to false,
//     which will then end the loading of the pushdown automata definition elsewhere in the application.
void StackAlphabet::load(ifstream& definition, bool& valid)
{
    string value;
    while((definition >> value) && (uppercase(value) != "TRANSITION_FUNCTION:"))
    {
        string uppercaseValue = uppercase(value);
        if((uppercaseValue == "STATES:") || (uppercaseValue == "INPUT_ALPHABET:") || (uppercaseValue == "STACK_ALPHABET:") || (uppercaseValue == "INITIAL_STATE:") || (uppercaseValue == "BLANK_CHARACTER:") || (uppercaseValue == "FINAL_STATES:"))
        {
            cout << "Improper keyword used in Stack Alphabet: " << uppercaseValue << endl;
            valid = false;
            return;
        }
        if(value.length() == 1 && (value[0] != '\\') && (value[0] != '[') && (value[0] != ']') && (value[0] != '<') && (value[0] != '>') && (value[0] > '!') && (value[0] < '~'))
        {
            alphabet.push_back(value[0]);
        }
        else
        {
            cout << "Illegal stack alphabet character " << value << endl;
            valid = false;
        }
    }
    if(definition.eof())
    {
        cout << "End of file reached too soon." << endl;
        valid = false;
    }
}

// The method view prints out the stack alphabet.
void StackAlphabet::view() const
{
    cout << "\u0393 = {";
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
// If value is found within the stack alphabet, true is returned.
// Otherwise, false is returned.
bool StackAlphabet::isElement(const char value) const
{
    bool isElement = false;
    for(vector<char>::const_iterator it = alphabet.begin(); it != alphabet.end(); ++it)
    {
        if(*it == value)
        {
            isElement = true;
            break;
        }
    }
    return isElement;
}