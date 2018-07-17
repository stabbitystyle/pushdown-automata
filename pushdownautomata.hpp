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

class PushdownAutomata
{
    private:
        InputAlphabet inputAlphabet;
        StackAlphabet stackAlphabet;
        TransitionFunction transitionFunction;
        States states;
        FinalStates finalStates;
        
        string initialState;
		char initialStackCharacter;
		vector<string> description;

        string currentState;
        string originalInputString;
		int numberOfTransitionsInSuccessfulPath;
        int numberOfTransitions;
        int numberOfCrashes;
        bool valid;
        bool used;
        bool operating;
        bool accepted;
        bool rejected;

        static ConfigurationSettingsPointer configurationSettingsPointer;

		void loadInitialState(ifstream& definition, bool& valid);
		void loadInitialStackCharacter(ifstream& definition, bool& valid);
    public:
        PushdownAutomata(string definitionFileName);
        void viewDefinition() const;
        void initialize(string inputString);
        bool isAccepted(InstantaneousDescription id, int numberInCurrentPath);
        void terminateOperation();
        string inputString() const;
        int totalNumberOfTransitions() const;
		int totalNumberOfCrashes() const;
        bool isValidDefinition() const;
        bool isValidInputString(string value) const;
        bool isUsed() const;
        bool isOperating() const;
        bool isAcceptedInputString() const;
        bool isRejectedInputString() const;

        static void link(ConfigurationSettings& configurationSettings);
};
typedef PushdownAutomata* PushdownAutomataPointer;

#endif