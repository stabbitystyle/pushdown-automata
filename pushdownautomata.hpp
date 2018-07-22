// Pushdown Automata class
// Rev0 7/4/18 by William Frank

#ifndef PUSHDOWNAUTOMATA_HPP
#define PUSHDOWNAUTOMATA_HPP

#include <string>
#include <vector>

#include "inputalphabet.hpp"
#include "stackalphabet.hpp"
#include "states.hpp"
#include "finalstates.hpp"
#include "transitionfunction.hpp"
#include "instantaneousdescription.hpp"
#include "configurationsettings.hpp"

using namespace std;

class CommandsInOperation;
class Commands;

class PushdownAutomata
{
    private:
        InputAlphabet inputAlphabet;
        StackAlphabet stackAlphabet;
        TransitionFunction transitionFunction;
        States states;
        FinalStates finalStates;
        CommandsInOperation* commands;

        string initialState;
		char initialStackCharacter;
		vector<string> description;

        //string commandcallpasser;

        string currentState;
        string originalInputString;
		int numberOfTransitionsInSuccessfulPath;
        int numberOfTransitions;
        int numberOfCrashes;
        int transitionCount;
        bool valid;
        bool used;
        bool operating;
        bool accepted;
        bool rejected;

        static ConfigurationSettingsPointer configurationSettingsPointer;

		void loadInitialState(ifstream& definition, string& value, bool& valid);
		void loadInitialStackCharacter(ifstream& definition, string& value, bool& valid);
    public:
        PushdownAutomata(string definitionFileName, Commands& cmd);
        void viewDefinition() const;
        string initialize(string inputString);
        bool isAccepted(InstantaneousDescription id, int numberInCurrentPath,bool& running, string& commandCalled);
        void terminateOperation();
        void resetTransitionCount();
        string inputString() const;
        int totalNumberOfTransitions() const;
		int totalNumberOfCrashes() const;
        bool isValidDefinition() const;
        bool isValidInputString(string value) const;
        bool isUsed() const;
        bool isOperating() const;
        bool isAcceptedInputString() const; 
        bool isRejectedInputString() const;
        void setCalledCommand(string value);

        static void link(ConfigurationSettings& configurationSettings);
};
typedef PushdownAutomata* PushdownAutomataPointer;

#endif