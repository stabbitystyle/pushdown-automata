// Int Input class
// Rev0 7/4/18 by William Frank

#include <string>
#include <iostream>
#include <cerrno>
#include <iterator>
#include <cstdlib>
#include <climits>

#include "intinput.hpp"

using namespace std;

// intInput is a non-negative int parser from a line of user input.  it filters out overflows and invalid characters
// (such at decimals, negative signs, letters, and other non-digit characters)
// returns a boolean if the input was valid and if it was, modifies the parameter userInput for use outside the function
bool intInput(int& userInput)
{
    string inputString;
    bool validInput = true;
    long inputNumber;
    getline(cin, inputString);
    for(string::iterator it = inputString.begin(); it != inputString.end(); ++ it)
    {
        if(!isdigit(*it))
        {
            cout << "Input contained an invalid character." << endl;
            validInput = false;
            break;
        }
    }
    if(validInput)
    {
        errno = 0;
        inputNumber = strtol(inputString.c_str(), NULL, 10);
        if(errno == ERANGE || inputNumber > INT_MAX)
        {
            cout << "Input was too large for an int.  Maximum int size is: " << INT_MAX << endl;
            validInput = false;
        }
        else
        {
            userInput = (int)inputNumber;
        }
    }
    
   return validInput;
}