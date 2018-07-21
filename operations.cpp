// Operations functions
// Rev0 7/15/18 by William Frank 

#include <string>

#include "operations.hpp"

using namespace std;

// ????
string truncated(string value, int maxNumberOfCharacters)
{
    if ((int)value.length() > maxNumberOfCharacters)
    value = value.substr(0, maxNumberOfCharacters) + ">";
    return value;
}

// ????
string visible(string value)
{
    const string lambda("\\");
    if (value.empty())
    {
        value = lambda;
    }
	return value;
}