#ifndef TRANSITIONFUNCTION_HPP
#define TRANSITIONFUNCTION_HPP

#include <string>
#include <vector>
#include <fstream>

#include "transition.hpp"
#include "stackalphabet.hpp"
#include "states.hpp"
#include "finalstates.hpp"
#include "instantaneousdescription.hpp"

using namespace std;

// The class TransitionFunction is a class which is responsible for storing and looking up transition functions for the pushdown automata.
class TransitionFunction
{
	private:
		vector<Transition> transitions;
	public:
		void load(ifstream& definition, bool& valid);
        //void validate(const TapeAlphabet& tapeAlphabet, const States& states, const FinalStates& finalStates, bool& valid) const;
		void view() const;
        void findTransitions(string sourceState, char readCharacter, char topOfStack, vector<Transition>& transitions) const;
		int transitionCount(string state, char inputCharacter, char stackCharacter);
		int lambdaTransitionCount(string state, char topOfStack);
		void getTransition(int index, string state, char inputCharacter, char stackCharacter, string destinationState, string pushString);
		void getLambdaTransition(int index, string state, char stackCharacter, string destinationState, string pushString);
};

#endif