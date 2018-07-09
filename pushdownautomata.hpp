// Pushdown Automata class
// Rev0 7/4/18 by William Frank

#ifndef PUSHDOWNAUTOMATA_HPP
#define PUSHDOWNAUTOMATA_HPP

#include <string>
#include <vector>

#include "instantaneous_description.hpp"

using namespace std;

class PushdownAutomata
{
    private:
        vector<string> description;
        string initialState;
        string currentState;
        char initialStackCharacter;
        string originalInputString;
        int numberOfTransitions;
        InstantaneousDescription initialID;
        int numberOfCrashes;
        int numberOfTransitionsInSuccessfulPath;
        bool valid;
        bool used;
        bool operating;
        bool accepted;
        bool rejected;
    public:
        PushdownAutomata(string definitionFileName);
        void viewDefinition() const;
        void initialize(string inputString);
        bool isAccepted(InstantaneousDescription id, int numberInCurrentPath);
        void terminateOperation();
        string inputString() const;
        int totalNumberOfTransitions() const;
        bool isValidDefinition() const;
        bool isValidInputString(string value) const;
        bool isUsed() const;
        bool isOperating() const;
        bool isAcceptedInputString() const;
        bool isRejectedInputString() const;
};

#endif