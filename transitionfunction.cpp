#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "transitionfunction.hpp"
#include "transition.hpp"
#include "stackalphabet.hpp"
#include "states.hpp"
#include "finalstates.hpp"
#include "uppercase.hpp"

using namespace std;

// The method load accepts a definition file and a valid Boolean as parameters.
// The definition file is checked for transition functions, which are then loaded into the transitions TransitionVector attribute.
// If there are any characters without spaces between them, if the transition function keyword cannot be found, if there is a duplicate function,
//     if one of the reserved characters is used within any of the transition functions, or if the next keyword after the transition function isn’t found,
//     valid is set to false, which will then terminate the Turing machine application elsewhere in the application.
void TransitionFunction::load(ifstream& definition, string& value, bool& valid)
{
    int i = 1;
    string sourceState;
    string destinationState;
    string pushString;
    char readCharacter = ' ';
    char stackCharacter = ' ';

    while((definition >> value) && (uppercase(value) != "INITIAL_STATE:"))
    {
        string uppercaseValue = uppercase(value);
        if((uppercaseValue == "STATES:") || (uppercaseValue == "INPUT_ALPHABET:") || (uppercaseValue == "STACK_ALPHABET:")
           || (uppercaseValue == "TRANSITION_FUNCTION:") || (uppercaseValue == "START_CHARACTER:") || (uppercaseValue == "FINAL_STATES:"))
        {
            cout << "Improper keyword used in Transition Function: " << uppercaseValue << "." << endl;
            valid = false;
            return;
        }

        switch(i)
        {
            // Source State
            case 1:
            {
                for(string::iterator it = value.begin(); it != value.end(); ++it)
                {
                    if((!isalnum(*it)) && (*it != '_'))
                    {
                        cout << "Illegal character used in transition function source state: " << value << endl;
                        valid = false;
                    }
                }
                if(valid != false)
                {
                    sourceState = value;
                }
                i++;
                break;
            }
            // Read Character
            case 2:
            {
                if(value.length() == 1 && (value[0] != '(') && (value[0] != ')') && (value[0] != ',') && (value[0] != '>'))
                {
                    readCharacter = value[0];
                }
                else
                {
                    cout << "Illegal transition function read character: " << value << endl;
                    valid = false;
                }
                i++;
                break;
            }
            // stack character
            case 3:
            {
                if(value.length() == 1 && (value[0] != '\\') && (value[0] != '(') && (value[0] != ')') && (value[0] != ',') && (value[0] != '>'))
                {
                    stackCharacter = value[0];
                }
                else
                {
                    cout << "Illegal transition function stack character: " << value << endl;
                    valid = false;
                }
                i++;
                break;
            }
            // Destination State
            case 4:
            {
                for(string::iterator it = value.begin(); it != value.end(); ++it)
                {
                    if((!isalnum(*it)) && (*it != '_'))
                    {
                        cout << "Illegal character used in transition function destination state: " << value << endl;
                        valid = false;
                    }
                }
                if(valid != false)
                {
                    destinationState = value;
                }
                i++;
                break;
            }
            // Push String
            case 5:
            {
                for(string::iterator it = value.begin(); it != value.end(); ++it)
                {
                    if((*it == '(') || (*it == ')') || (*it == ',') || (*it == '>'))
                    {
                        cout << "Illegal transition function push string: " << value << endl;
                        valid = false;
                    }
                }

                if(valid != false)
                {
                    pushString = value;
                    Transition newTransition(sourceState, readCharacter, destinationState, stackCharacter, pushString);
                    transitions.push_back(newTransition);
                }

                i = 1;
                break;
            }
        }
    }
    // didn't fill out a full transition function
    if(i != 1 && valid != false)
    {
        cout << "End of transition function finished with less components than necessary." << endl;
        valid = false;
    }
    if(definition.eof())
    {
        cout << "End of file reached too soon." << endl;
        valid = false;
    }
}

// The method validate checks whether each of the transitions found within the transitions vector contain valid states and characters.
 void TransitionFunction::validate(const StackAlphabet& stackAlphabet, const InputAlphabet& inputAlphabet, const States& states, const FinalStates& finalStates, bool& valid) const
 {
     for(int index = 0; index < (int)transitions.size(); ++index)
 	{
         if(!states.isElement(transitions[index].sourceState()))
         {
             cout << "Source state " << transitions[index].sourceState() << " is not in states.\n";
             valid = false;
         }
        if(!states.isElement(transitions[index].destinationState()))
         {
             cout << "Destination state " << transitions[index].destinationState() << " is not in states.\n";
             valid = false;
         }
         if(!inputAlphabet.isElement(transitions[index].readCharacter()))
         {
             cout << "Read character " << transitions[index].readCharacter() << " is not in input alphabet.\n";
             valid = false;
         }
         if(!stackAlphabet.isElement(transitions[index].stackCharacter()))
         {
             cout << "Stack character " << transitions[index].stackCharacter() << " is not in stack alphabet.\n";
             valid = false;
         }
         for(size_t i = 0; i < transitions[index].pushString().size();i++){
             if(!stackAlphabet.isElement(transitions[index].pushString()[i]) && transitions[index].pushString()[i] != '\\'){
                 cout << "Push string " << transitions[index].pushString() << " contains characters not in stack alphabet.\n";
                 valid = false;
             }
         }
     }
 }

// The method view prints out all of the transition functions in the pushdown automata, stored in the attribute transitions.
void TransitionFunction::view() const
{
    if(transitions.empty())
    {
        cout << "There are no transition functions." << endl;
    }
    for(vector<Transition>::const_iterator it = transitions.begin(); it != transitions.end(); ++it)
    {
        bool alreadyUsed = false;
        for(vector<Transition>::const_iterator sub = transitions.begin(); sub != it; ++sub)
        {
            if((sub->sourceState() == it->sourceState()) && (sub->readCharacter() == it->readCharacter()) && (sub->stackCharacter() == it->stackCharacter()))
            {
                alreadyUsed = true;
            }
        }
        if(alreadyUsed == false)
        {
            cout << "\u03B4(" << it->sourceState() << ", " << it->readCharacter() << ", " << it->stackCharacter() << ") = {(" << it->destinationState() << ", " << it->pushString() << ")";
            for(vector<Transition>::const_iterator sub = it + 1; sub != transitions.end(); ++sub)
            {
                if((sub->sourceState() == it->sourceState()) && (sub->readCharacter() == it->readCharacter()) && (sub->stackCharacter() == it->stackCharacter()))
                {
                    cout << ", (" << sub->destinationState() << ", " << sub->pushString() << ")";
                }
            }
            cout << "}" << endl;
        } 
    }
}

// The method findTransitions accepts a sourceState string, a readCharacter character, a topOfStack character,
//     and a transitions Transition vector as parameters.
// The method findTransition looks through the attribute transitions, which is a vector of all of the transitions in the pushdown automata,
//     to find a transition that matches the state from sourceState, the current symbol from readCharacter, and the symbol from topOfStack.
// The method then returns by reference a vector of all of the valid transitions
void TransitionFunction::findTransitions(string sourceState, char readCharacter, char topOfStack, vector<Transition>& transitionsParameter) const
{
    // for(vector<Transition>::iterator it = transitions.begin(); it != transitions.end(); ++it)
    // {
    //     if((*it.sourceState() == sourceState) && (*it.readCharacter() == readCharacter) && (*it.stackCharacter() == topOfStack))
    //     {
    //         transitionsParameter.push_back(*it);
    //     }
    // }
    for(int index = 0; index < (int)transitions.size(); ++index)
	{
        if((transitions[index].sourceState() == sourceState) && (transitions[index].readCharacter() == readCharacter) && (transitions[index].stackCharacter() == topOfStack))
        {
            transitionsParameter.push_back(transitions[index]);
        }
	}
}

//Returns the number of transitions available for a given configuration of state, lambdacharacter, and stackcharacter
int TransitionFunction::lambdaTransitionCount(string state, char topOfStack)
{
    vector<Transition> temp;
    findTransitions(state, '\\', topOfStack, temp);
    return temp.size();
}

//Returns the number of transitions available for a given configuration of state, inputcharacter, and stackcharacter
int TransitionFunction::transitionCount(string state, char inputCharacter, char stackCharacter)
{
    vector<Transition> temp;
    findTransitions(state, inputCharacter, stackCharacter, temp);
    return temp.size();
}

//Find the transitions that matches the state, inputCharacter, and stackCharacter params sent in. Then chooses one based
//on what index value is set. Sets the destinationState and pushString values by reference for the user.
void TransitionFunction::getTransition(int index, string state, char inputCharacter, char stackCharacter, string& destinationState, string& pushString)
{
    vector<Transition> temp;
    findTransitions(state, inputCharacter, stackCharacter, temp);
    destinationState = temp[index].destinationState();
    pushString = temp[index].pushString();
}

//Find the transitions that matches the state, lambdaCharacter, and stackCharacter params sent in. Then chooses one based
//on what index value is set. Sets the destinationState and pushString values by reference for the user.
void TransitionFunction::getLambdaTransition(int index, string state, char stackCharacter, string& destinationState, string& pushString)
{
    vector<Transition> temp;
    findTransitions(state, '\\', stackCharacter, temp);
    destinationState = temp[index].destinationState();
    pushString = temp[index].pushString();
}