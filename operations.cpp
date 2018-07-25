// Operations functions
// Rev0 7/15/18 by William Frank 

#include <string>

#include "operations.hpp"

using namespace std;

//this method returns a string that if it is longer then the maxNumberOfCharacters
//will truncate the string and append a > to the end.
//if not it will return the string unchanged.
string truncated(string value, int maxNumberOfCharacters)
{
    if ((int)value.length() > maxNumberOfCharacters)
    value = value.substr(0, maxNumberOfCharacters) + ">";
    return value;
}

//this method replaces an empty string with a "\"
string visible(string value)
{
    const string lambda("\\");
    if (value.empty())
    {
        value = lambda;
    }
	return value;
}