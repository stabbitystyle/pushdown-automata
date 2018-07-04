// Uppercase class
// Rev0 7/4/18 by William Frank

#include <string>
#include <iterator>
#include <ctype.h>

#include "uppercase.hpp"

using namespace std;

// converts a given string to uppercase
string uppercase(const string value)
{
    string toUpper = value;
    for(string::iterator it = toUpper.begin(); it != toUpper.end(); ++it)
    {
        *it = toupper(*it);
    }
    return toUpper;
}