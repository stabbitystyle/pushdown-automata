#ifndef TRANSITIONFUNCTION_HPP
#define TRANSITIONFUNCTION_HPP

#include <string>
#include <vector>
#include <fstream>
#include <string>

#include "transition.hpp"
#include "stackalphabet.hpp"
#include "inputalphabet.hpp"
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
		void load(ifstream& definition, string& value, bool& valid);
		void validate(const StackAlphabet& stackAlphabet, const InputAlphabet& inputAlphabet, const States& states, const FinalStates& finalStates, bool& valid) const;
		void view() const;
		void findTransitions(string sourceState, char readCharacter, char topOfStack, vector<Transition>& transitions) const;
		int transitionCount(string state, char inputCharacter, char stackCharacter);
		int lambdaTransitionCount(string state, char topOfStack);
		void getTransition(int index, string state, char inputCharacter, char stackCharacter, string destinationState, string pushString);
		void getLambdaTransition(int index, string state, char stackCharacter, string destinationState, string pushString);
		void getLambdaTransitions(string state, char stackCharacter,vector<Transition>& list);
		void getTransitions(string state, char inputCharacter, char stackCharacter, vector<Transition>& list);
};

#endif