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
void TransitionFunction::load(ifstream& definition, bool& valid)
{
    string value;
    int i = 1;
    string sourceState;
    string destinationState;
    string pushString;
    char readCharacter = ' ';
    char stackCharacter = ' ';

    while((valid != false) && (definition >> value) && (uppercase(value) != "INITIAL_STATE:"))
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
                        cout << "Illegal character used in transition function state: " << value << endl;
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
                if(value.length() == 1 && (value[0] != '\\') && (value[0] != '(') && (value[0] != ')') && (value[0] != ',') && (value[0] != '>'))
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
            // Destination State
            case 3:
            {
                for(string::iterator it = value.begin(); it != value.end(); ++it)
                {
                    if((!isalnum(*it)) && (*it != '_'))
                    {
                        cout << "Illegal character used in transition function state: " << value << endl;
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
            // Stack Character
            case 4:
            {
                if(value.length() == 1 && (value[0] != '\\') && (value[0] != '(') && (value[0] != ')') && (value[0] != ',') && (value[0] != '>'))
                {
                    stackCharacter = value[0];
                }
                else
                {
                    cout << "Illegal transition function write character: " << value << endl;
                    valid = false;
                }
                i++;
                break;
            }
            // Push String
            case 5:
            {
                for(string::iterator it = value.begin(); it != value.end(); ++it)
                {
                    if((*it == '\\') || (*it == '(') || (*it == ')') || (*it == ',') || (*it == '>'))
                    {
                        cout << "Illegal transition function read character: " << value << endl;
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

// // The method validate checks whether each of the transitions found within the transitions vector contain valid states and characters.
// void TransitionFunction::validate(const StackAlphabet& stackAlphabet, const States& states, const FinalStates& finalStates, bool& valid) const
// {
//     for(int index = 0; index < (int)transitions.size(); ++index)
// 	{
// 		if(finalStates.isElement(transitions[index].sourceState()))
//         {
//             cout << "Source state " << transitions[index].sourceState() << " is in final states.\n";
//             valid = false;
//         }
//         if(! states.isElement(transitions[index].sourceState()))
//         {
//             cout << "Source state " << transitions[index].sourceState() << " is not in states.\n";
//             valid = false;
//         }
//         if(! tapeAlphabet.isElement(transitions[index].readCharacter()))
//         {
//             cout << "Read character " << transitions[index].readCharacter() << " is not in tape alphabet.\n";
//             valid = false;
//         }
//         if(! tapeAlphabet.isElement(transitions[index].writeCharacter()))
//         {
//             cout << "Write character " << transitions[index].writeCharacter() << " is not in tape alphabet.\n";
//             valid = false;
//         }
//     }
// }

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
            for(vector<Transition>::const_iterator sub = it; sub != transitions.end(); ++sub)
            {
                if((sub->sourceState() == it->sourceState()) && (sub->readCharacter() == it->readCharacter()) && (sub->stackCharacter() == it->stackCharacter()))
                {
                    cout << ", (" << it->destinationState() << ", " << it->pushString() << ")";
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
    for(int index = 0; index < (int)transitions.size(); ++index)
	{
        if((transitions[index].sourceState() == sourceState) && (transitions[index].readCharacter() == readCharacter) && (transitions[index].stackCharacter() == topOfStack))
        {
            transitionsParameter.push_back(transitions[index]);
        }
	}
}
