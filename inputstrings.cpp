// Input Strings class
// Rev0 7/4/18 by William Frank
// Rev1 7/10/18 by Cole Woodford

#include <string>
#include <iostream>
#include <fstream>
#include <iterator>
#include<algorithm>

#include "inputstrings.hpp"
#include "pushdownautomata.hpp"

using namespace std;

static bool stringCompaire(const string& right, const string& left);

InputStrings::InputStrings() : stringListModified(false)
{
}

// The method load accepts stringFileName as a parameter.
// The parameter stringFileName is the name of the file containing the list of strings to be used in the pushdown automata application.
// The method load reads the stringFileName file, verifies that they’re valid strings to test against the pushdown automata, 
// and if they are, they’re added to the strings attribute.
// If not, they are ignored and the stringListModified attribute is set to true.
void InputStrings::load(string stringFileName, const PushdownAutomata& pushdownAutomata)
{
    ifstream definition(stringFileName.c_str(), ifstream::in);
    string value;
    notSorted = true;
    if(definition.fail())
    {
        cout << "Failed to open input string file." << endl;
    }
    while(!definition.fail() && getline(definition, value))
    {
        for(string::iterator it = value.begin(); it != value.end(); ++it)
        {
            if(isspace(*it) || (value.find('\\') != string::npos && value.size() != 1))
            {
                cout << value << " is rejected." << endl;
                stringListModified = true;
                break;
            }
        }
        if(pushdownAutomata.isValidInputString(value) && !isElement(value))
        {
            strings.push_back(value);
        }
        else
        {
            cout << value << "is invalid input string." << endl;
            stringListModified = true;
        }
    }
    if(stringListModified)
    {
        //cout << "String list removed some strings while loading." << endl;
    }
    else if(!definition.fail())
    {
        //cout << "String list loaded correctly." << endl;
    }
}

// The method getInputString accepts stringIndex as a parameter.
// The parameter stringIndex is the index of the string from the strings attribute to return.
// The method getInputString then returns that string.
string InputStrings::getInputString(int stringIndex) const
{
    return strings[stringIndex - 1];
}

// The method view prints out the contents of the attribute strings.
void InputStrings::view() const
{
    int i = 1;
    for(vector<string>::const_iterator it = strings.begin(); it != strings.end(); ++it)
    {
        cout << i << ". " << *it << endl;
        i++;
    }
}

// The method isElement accepts a string inputString as a parameter.
// It then checks to see if inputString is in the attribute vector strings.
// If it is, true is returned; otherwise, false is returned.
bool InputStrings::isElement(string inputString) const
{
    bool isElement = false;
    for(vector<string>::const_iterator it = strings.begin(); it != strings.end(); ++it)
    {
        if(*it == inputString)
        {
            isElement = true;
            break;
        }
    }
    return isElement;
}

// The method addToStrings accepts a string inputString as a parameter.
// It checks with isElement before adding it to the string list.
// error checking done in commands, assuming safe string
void InputStrings::addToStrings(string inputString)
{
    strings.push_back(inputString);
    stringListModified = true;
    notSorted = true;
}

// The method removeFromStrings accepts an integer stringIndex, which is the index of the string to delete + 1, as a parameter.
// The string with that index in the vector is then removed from the vector.
void InputStrings::removeFromStrings(int stringIndex)
{
    strings.erase(strings.begin() + (stringIndex - 1));
    stringListModified = true;
    notSorted = true;
}

// The method saveToFile accepts a string stringFileName as a parameter.
// It then checks the attribute stringListModified to see if the string list has been modified and therefore the string list needs to be written to file.
// If the file needs to be written, the method attempts to write the list to file and prints a message upon success or failure.
// If it doesn’t need to write, then nothing is done and no output is produced.
void InputStrings::saveToFile(string stringFileName)
{
    if(stringListModified)
    {
        ofstream stringFile(stringFileName.c_str(), ofstream::out);
        if(stringFile.fail())
        {
            cout << "Error: The string list file could not be modified." << endl;
        }
        else
        {
            for(vector<string>::const_iterator it = strings.begin(); it != strings.end(); ++it)
            {
                stringFile << *it << endl;
            }
            stringFile.close();
            if(stringFile.fail())
            {
                cout << "Error: failed to close " << stringFileName << "." << endl;
            }
            else
            {
                cout << "The string list file has been successfully modified." << endl;
            }
        }
        cout << endl;
    }
}

// The method numberOfStrings returns the number of strings found in the strings StringVector attribute.
int InputStrings::numberOfStrings() const
{
    return strings.size();
}

// The method sort sorts the inputStrings strings vector attribute into canonical order
void InputStrings::sort()
{
    if(notSorted){
        std::sort(strings.begin(),strings.end());
        std::sort(strings.begin(),strings.end(),stringCompaire);
        notSorted =false;
    }else{
        cout << "strings alrerady sorted" << endl;
    }


}

static bool stringCompaire(const string& right, const string& left){
    
    /*
    if(right.length() > left.length()){
        return false;
    }else if(right > left){
        return false;
    }
    return true;
    */
   return !(right.length() > left.length());

}

