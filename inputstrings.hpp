// Input Strings class
// Rev0 7/4/18 by William Frank
// Rev1 7/10/18 by Cole Woodford

#ifndef INPUTSTRINGS_HPP
#define INPUTSTRINGS_HPP

#include <string>
#include <vector>

#include "pushdownautomata.hpp"

using namespace std;

// The InputStrings class is a class which is responsible for holding the string list, 
// which is the list of strings the user might want to test against the pushdown automata.
// It can add and remove strings from the list, display the list, and save the list to 
// file if the list changed from the original list at any point.
class InputStrings
{
    private:
        vector<string> strings;
        bool stringListModified;
        bool notSorted;
    public:
        InputStrings();
        void load(string stringFileName, const PushdownAutomata& pushdownAutomata);
        string getInputString(int stringIndex) const;
        void view() const;
        bool isElement(string inputString) const;
        void addToStrings(string inputString);
        void removeFromStrings(int stringIndex);
        void saveToFile(string stringFileName);
        int numberOfStrings() const;
		void sort();
};

#endif