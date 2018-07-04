// Tape Alphabet class
// Rev0 7/4/18 by William Frank

#include <fstream>
#include <iostream>
#include <iterator>

#include "tapealphabet.hpp"
#include "uppercase.hpp"

using namespace std;

// The method load accepts a definition file and a valid Boolean as parameters.
// The definition file is checked for the tape alphabet, which is then loaded into the alphabet attribute.
// If there are any characters without spaces between them, if the tape alphabet keyword cannot be found,
//     if one of the tape alphabet characters is from the reserved list of characters, if there are any duplicate characters,
//     or if the next keyword after the input alphabet isn’t found, valid is set to false,
//     which will then end the loading of the pushdown automata definition elsewhere in the application.
// Load also checks whether all of the characters from the input alphabet is contained in the tape alphabet.
// And it also checks whether the blank character is in the tape alphabet.
void TapeAlphabet::load(ifstream& definition, bool& valid)
{
    string value;
    while((definition >> value) && (uppercase(value) != "TRANSITION_FUNCTION:"))
    {
        string uppercaseValue = uppercase(value);
        if((uppercaseValue == "STATES:") || (uppercaseValue == "INPUT_ALPHABET:") || (uppercaseValue == "TAPE_ALPHABET:") || (uppercaseValue == "INITIAL_STATE:") || (uppercaseValue == "BLANK_CHARACTER:") || (uppercaseValue == "FINAL_STATES:"))
        {
            cout << "Improper keyword used in Tape Alphabet: " << uppercaseValue << endl;
            valid = false;
            return;
        }
        if(value.length() == 1 && (value[0] != '\\') && (value[0] != '[') && (value[0] != ']') && (value[0] != '<') && (value[0] != '>') && (value[0] >= '!') && (value[0] <= '~'))
        {
            alphabet.push_back(value[0]);
        }
        else
        {
            cout << "Illegal tape alphabet character " << value << endl;
            valid = false;
        }
    }
    if(definition.eof())
    {
        cout << "End of file reached too soon." << endl;
        valid = false;
    }
}

// The method view prints out the tape alphabet.
void TapeAlphabet::view() const
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
// If value is found within the tape alphabet, true is returned.
// Otherwise, false is returned.
bool TapeAlphabet::isElement(const char value) const
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